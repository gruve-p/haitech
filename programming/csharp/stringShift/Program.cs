using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace StringShift
{
    class Program
    {
        static void Main(string[] args)
        {
            StrShift hai = new StrShift();
            hai = "Microsoft";
            Console.WriteLine("hai>>2 results in "+(hai >> 2));
            StrShift hai_b = new StrShift();
            hai_b = "crosoftMi";
            Console.WriteLine("hai==hai_b:" + (hai == hai_b).ToString());
            Console.WriteLine(hai << 1);
            Console.WriteLine("hai!=hai_b:" + (hai != hai_b).ToString());
            Console.WriteLine(hai << 1);
        }
    }

    public class StrShift
    {
        public string myString = "haiphan";
        public static string operator <<(StrShift hai, int i)
        {
            if (hai == null) { return "ERROR - object contains string is null???"; }
            if (hai.myString == null) { return "ERROR - the string is null???"; }
            if (i < 0) { return "ERROR - The integer mus be positive"; }
            if (hai.myString.Length < i) { return "ERROR - The integer exceed the string length"; }
            string s = hai.myString;
            int l = s.Length;
            hai.myString = s.Substring(l - i) + s.Substring(0, l - i);
            //Console.WriteLine("DEBUGGING... << returned:  " + hai.myString);
            return hai.myString;
        }
        public static string operator >>(StrShift hai, int i)
        {
            if (hai == null) { return "ERROR - object contains string is null???"; }
            if (hai.myString == null) { return "ERROR - the string is null???"; }
            if (i < 0) { return "ERROR - The integer mus be positive"; }
            if (hai.myString.Length < i) { return "ERROR - The integer exceed the string length"; }
            string s = hai.myString;
            int l = s.Length;
            hai.myString = s.Substring(i, l - i) + s.Substring(0, i);
            //Console.WriteLine("DEBUGGING... >> returned:  " + hai.myString);
            return hai.myString;
        }
        public static bool operator ==(StrShift hai1, StrShift hai2)
        {
            if (System.Object.ReferenceEquals(hai1, hai2))
            {
                return true;
            }
            if (((object)hai1 == null) || ((object)hai2 == null))
            {
                return false;
            }
            if (System.Object.ReferenceEquals(hai1.myString, hai2.myString)) return true;
            if (hai1.myString.Equals(hai2.myString)) return true;
            return false;
        }
        public static bool operator !=(StrShift hai1, StrShift hai2)
        {
            return !(hai1 == hai2);
        }
        public bool Equals(StrShift hai)
        {
            return (this == hai);
        }
        public static implicit operator StrShift(string s)
        {
            StrShift hai = new StrShift();
            hai.myString = s;
            return hai;
        }
        public static implicit operator String(StrShift hai)
        {
            return hai.myString;
        }
    }
}