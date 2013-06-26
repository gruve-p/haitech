using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using HPMoneyChange;

namespace ChangeTest
{
    [TestClass]
    public class ChangeTest
    {
        [TestMethod]
        public void TestChangeMaker()
        {
            Assert.AreEqual(4, MoneyChanger.MakeChange(135), 0, "number of changes not correct");
            Assert.AreEqual(1, MoneyChanger.MakeChange(100), 0, "number of changes not correct");
            Assert.AreEqual(8, MoneyChanger.MakeChange(99), 0, "number of changes not correct");
        }
    }
}
