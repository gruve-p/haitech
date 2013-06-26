using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace HPMoneyChange
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine(MoneyChanger.MakeChange(135));
            Console.WriteLine(MoneyChanger.MakeChange(213));
            Console.WriteLine(MoneyChanger.MakeChange(123));
        }
    }
    public class MoneyChanger
    {
        public static int MakeChange(int amount)
        {
            int[] coins = new int[6] { 100, 50, 20, 10, 5, 1 };
            int ncoin = 0;
            for (int i = 0; i < coins.Length ;i++ ){
                int num = amount / coins[i];
                ncoin += num;
                amount -= coins[i] * num;
            }
            //Console.WriteLine(ncoin.ToString());
            return ncoin;

        }

    }
}
