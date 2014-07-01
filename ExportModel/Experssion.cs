﻿using Aveva.Pdms.Database;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ExportModel
{
	public class Experssion
	{
		private string exper;
		private IOperator op = null;
		public string Exper
		{
			get
			{
				return exper;
			}
		}

		public DbElement ModelElement { get; set; }

		public Experssion(string exper)
		{
			this.exper = exper.ToUpper();
			Parse();
		}

		private bool IsSplit(char ch)
		{
			return Char.IsWhiteSpace(ch) || ch == '[' || ch == ']';
		}

		private bool SkipSpace(CharEnumerator iter)
		{
			while(IsSplit(iter.Current))
			{
				if (!iter.MoveNext())
					return false;
			}
			return true;
		}

		private bool IsOp(char ch)
		{
			return ch == '+' || ch == '-' || ch == '*' || ch == '/';
		}

		public void Parse()
		{
			CharEnumerator experIter = Exper.GetEnumerator();
			if (experIter.MoveNext())
				Parse(experIter, OperatorOrder.NONE, ref op);
			else
				op = new ValOp(0.0);
		}

		public double Eval(DbElement ele)
		{
			ModelElement = ele;
			return op.Eval();
		}

		enum OperatorOrder
		{
			NONE,
			NEED_OPERATOR,
			NEED_VALUE
		};

		private bool Parse(CharEnumerator experIter, IOperator prevOp, ref IOperator op)
		{
			if (!SkipSpace(experIter))
				return true;

			char curCh = experIter.Current;
			bool isEof = false;
			if (IsOp(curCh))
			{
				isEof = !experIter.MoveNext();

				IOperator valueOp = null;
				if (isEof)
					throw new FormatException();
				isEof = Parse(experIter, OperatorOrder.NEED_VALUE, ref valueOp);
				switch (curCh)
				{
					case '-':
						{
							if (!isEof)
							{
								IOperator nextValueOp = null;
								isEof = !experIter.MoveNext();
								if (!isEof)
									isEof = Parse(experIter, valueOp, ref nextValueOp);
								if (nextValueOp == null)
									op = new SubOp(prevOp, valueOp);
								else
									op = new SubOp(prevOp, nextValueOp);
							}
							else
								op = new SubOp(prevOp, valueOp);
							break;
						}
					case '+':
						{
							if (!isEof)
							{
								IOperator nextValueOp = null;
								isEof = !experIter.MoveNext();
								if (!isEof)
									isEof = Parse(experIter, valueOp, ref nextValueOp);
								if (nextValueOp == null)
									op = new AddOp(prevOp, valueOp);
								else
									op = new AddOp(prevOp, nextValueOp);
							}
							else
								op = new AddOp(prevOp, valueOp);
							break;
						}
					case '*':
						op = new MulOp(prevOp, valueOp);
						break;
					case '/':
						op = new DivOp(prevOp, valueOp);
						break;
					default:
						throw new FormatException();
				}

				return isEof;
			}
			else if (curCh == '('
				|| curCh == ')')
			{
				throw new FormatException();
			}
			else
			{
				isEof = ParseItem(experIter, OperatorOrder.NEED_OPERATOR, ref op);
				if (op is TwoObjOp)
					((TwoObjOp)op).LhsItem = prevOp;
			}
			return isEof;
		}

		private bool Parse(CharEnumerator experIter, OperatorOrder opOrder, ref IOperator op)
		{
			op = null;
			if (!SkipSpace(experIter))
				return true;

			bool isEof = false;
			if (IsOp(experIter.Current))
			{
				if (experIter.Current == '-')
				{
					isEof = !experIter.MoveNext();
					IOperator valueOp = null;
					if (!isEof)
						isEof = Parse(experIter, OperatorOrder.NEED_VALUE, ref valueOp);
					if (valueOp == null)
						throw new FormatException();
					op = new NegOp(valueOp);
				}
				else if (experIter.Current == '+')
				{
					isEof = !experIter.MoveNext();
					if (isEof)
						throw new FormatException();
					isEof = Parse(experIter, OperatorOrder.NEED_VALUE, ref op);
				}
				else
					throw new FormatException();
			}
			else if (experIter.Current == '(')
			{
				isEof = !experIter.MoveNext();
				if (isEof)
					throw new FormatException();

				if (!SkipSpace(experIter))
					throw new FormatException();

				isEof = Parse(experIter, OperatorOrder.NONE, ref op);
			}
			else if (experIter.Current == ')')
			{
				isEof = !experIter.MoveNext();
				return isEof;
			}
			else
			{
				isEof = ParseItem(experIter, OperatorOrder.NEED_VALUE, ref op);
			}

			while (!isEof && opOrder == OperatorOrder.NONE)
			{
				IOperator nextValueOp = null;
				isEof = Parse(experIter, op, ref nextValueOp);
				if (nextValueOp != null)
					op = nextValueOp;
			}

			return isEof;
		}

		private bool ParseItem(CharEnumerator experIter, OperatorOrder opOrder, ref IOperator op)
		{
			StringBuilder sb = new StringBuilder();
			bool isEof = false;
			while (!IsSplit(experIter.Current) && !IsOp(experIter.Current) && experIter.Current != '(' && experIter.Current != ')')
			{
				sb.Append(experIter.Current);
				if (!experIter.MoveNext())
				{
					isEof = true;
					break;
				}
			}

			string item = sb.ToString();
			if (Char.IsDigit(item[0]) || item[0] == '-' || item[0] == '+' || item[0] == '.')
			{
				op = new ValOp(Double.Parse(item));
				return isEof;
			}

			if (item.Equals("DDHEIGHT"))
			{
				op = new HeightOp(this);
				return isEof;
			}
			else if (item.Equals("DDANGLE"))
			{
				op = new AngleOp(this);
				return isEof;
			}
			else if (item.Equals("DDRADIUS"))
			{
				op = new RadiusOp(this);
				return isEof;
			}

			if (isEof)
				throw new FormatException();

			if (item.Equals("TIMES"))
			{
				IOperator valueOp = null;
				isEof = Parse(experIter, OperatorOrder.NEED_VALUE, ref valueOp);
				op = new MulOp(null, valueOp);
			}
			else if (item.Equals("DIFFERENCE"))
			{
				IOperator valueOp = null;
				isEof = Parse(experIter, OperatorOrder.NEED_VALUE, ref valueOp);
				IOperator nextValueOp = null;
				isEof = Parse(experIter, OperatorOrder.NEED_VALUE, ref nextValueOp);
				op = new SubOp(valueOp, valueOp);
			}
			else if (item.Equals("SUM"))
			{
				IOperator valueOp = null;
				isEof = Parse(experIter, OperatorOrder.NEED_VALUE, ref valueOp);
				IOperator nextValueOp = null;
				isEof = Parse(experIter, OperatorOrder.NEED_VALUE, ref nextValueOp);
				op = new AddOp(valueOp, valueOp);
			}
			else if (item.Equals("PARAM"))
			{
				ParamOp paramOp = new ParamOp(this);
				IOperator valueOp = null;
				isEof = Parse(experIter, OperatorOrder.NEED_VALUE, ref valueOp);
				paramOp.Item = valueOp;
				op = paramOp;
				return isEof;
			}
			else if (item.Equals("IPARAM"))
			{
				IParamOp paramOp = new IParamOp(this);
				IOperator valueOp = null;
				isEof = Parse(experIter, OperatorOrder.NEED_VALUE, ref valueOp);
				paramOp.Item = valueOp;
				op = paramOp;
				return isEof;
			}
			else if (item.Equals("DESIGN"))
			{
				while (!IsSplit(experIter.Current) && !IsOp(experIter.Current) && experIter.Current != '(' && experIter.Current != ')')
				{
					sb.Append(experIter.Current);
					if (!experIter.MoveNext())
					{
						isEof = true;
						break;
					}
				}

				if (isEof)
					throw new FormatException();

				if (item.Equals("PARAM"))
				{
					DParamOp paramOp = new DParamOp(this);
					IOperator valueOp = null;
					isEof = Parse(experIter, OperatorOrder.NEED_VALUE, ref valueOp);
					paramOp.Item = valueOp;
					op = paramOp;
					return isEof;
				}
				else
					throw new FormatException();
			}

			return isEof;
		}
	}

	interface IOperator
	{
		double Eval();
	}

	abstract class OneObjOp : IOperator
	{
		public OneObjOp()
		{

		}

		public OneObjOp(IOperator item)
		{
			Item = item;
		}

		public IOperator Item { get; set; }
		public virtual double Eval()
		{
			throw new NotImplementedException();
		}
	}

	abstract class TwoObjOp : IOperator
	{
		public TwoObjOp()
		{

		}

		public TwoObjOp(IOperator lhs, IOperator rhs)
		{
			LhsItem = lhs;
			RhsItem = rhs;
		}

		public IOperator LhsItem { get; set; }
		public IOperator RhsItem { get; set; }

		public virtual double Eval()
		{
			throw new NotImplementedException();
		}
	}

	class AddOp : TwoObjOp
	{
		public AddOp()
		{

		}

		public AddOp(IOperator lhs, IOperator rhs) : base(lhs, rhs)
		{

		}

		public override double Eval()
		{
			return LhsItem.Eval() + RhsItem.Eval();
		}
	}

	class SubOp : TwoObjOp
	{
		public SubOp()
		{

		}

		public SubOp(IOperator lhs, IOperator rhs) : base(lhs, rhs)
		{

		}

		public override double Eval()
		{
			return LhsItem.Eval() / RhsItem.Eval();
		}
	}

	class MulOp : TwoObjOp
	{
		public MulOp()
		{

		}

		public MulOp(IOperator lhs, IOperator rhs) : base(lhs, rhs)
		{

		}

		public override double Eval()
		{
			return LhsItem.Eval() * RhsItem.Eval();
		}
	}

	class DivOp : TwoObjOp
	{
		public DivOp()
		{

		}

		public DivOp(IOperator lhs, IOperator rhs) : base(lhs, rhs)
		{

		}

		public override double Eval()
		{
			return LhsItem.Eval() / RhsItem.Eval();
		}
	}

	class NegOp : OneObjOp
	{
		public NegOp()
		{

		}

		public NegOp(IOperator item) : base(item)
		{

		}

		public override double Eval()
		{
			return -Item.Eval();
		}
	}

	class ValOp : IOperator
	{
		public double Val { get; set; }

		public ValOp(double val)
		{
			Val = val;
		}

		public double Eval()
		{
			return Val;
		}
	}

	abstract class EleOp : OneObjOp
	{
		public Experssion Exper { get; set; }
		public EleOp(Experssion exper)
		{
			Exper = exper;
		}
	}

	class ParamOp : EleOp
	{
		public ParamOp(Experssion exper) : base(exper)
		{
		}

		public override double Eval()
		{
			DbElement spref = Exper.ModelElement.GetElement(DbAttributeInstance.SPRE);
			DbElement cate = spref.GetElement(DbAttributeInstance.CATR);
			return cate.GetDoubleArray(DbAttributeInstance.PARA)[(int)Item.Eval() - 1];
		}
	}

	class DParamOp : EleOp
	{
		public DParamOp(Experssion exper)
			: base(exper)
		{
		}

		public override double Eval()
		{
			return Exper.ModelElement.GetDoubleArray(DbAttributeInstance.PARA)[(int)Item.Eval() - 1];
		}
	}

	class IParamOp : EleOp
	{
		public IParamOp(Experssion exper)
			: base(exper)
		{
		}

		public override double Eval()
		{
			return Exper.ModelElement.GetElement(DbAttributeInstance.ISPE).GetDoubleArray(DbAttributeInstance.IPAR)[(int)Item.Eval() - 1];
		}
	}

	class HeightOp : EleOp
	{
		public HeightOp(Experssion exper) : base(exper)
		{

		}

		public override double Eval()
		{
			return Exper.ModelElement.GetDouble(DbAttributeInstance.HEIG);
		}
	}

	class AngleOp : EleOp
	{
		public AngleOp(Experssion exper)
			: base(exper)
		{

		}

		public override double Eval()
		{
			return Exper.ModelElement.GetDouble(DbAttributeInstance.ANGL);
		}
	}

	class RadiusOp : EleOp
	{
		public RadiusOp(Experssion exper)
			: base(exper)
		{

		}

		public override double Eval()
		{
			return Exper.ModelElement.GetDouble(DbAttributeInstance.RADI);
		}
	}
}
