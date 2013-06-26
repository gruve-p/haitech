using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using StringShift;

namespace StringShiftTest
{
    [TestClass]
    public class StringShiftTest
    {
        [TestMethod]
        public void TestRotateLeft()
        {
            StrShift hai = new StrShift();
            hai = "Microsoft";
            Assert.AreEqual("ftMicroso", hai<<2,"Left Rotate is not correct");
            hai = "haiphan";
            string dummy = hai << 1;
            dummy = hai << 1;
            Assert.AreEqual("anhaiph", dummy, "Left Rotate is not correct");
        }

        [TestMethod]
        public void TestRotateRight()
        {
            StrShift hai = new StrShift();
            hai = "Microsoft";
            Assert.AreEqual("crosoftMi", hai >> 2, "Right Rotate is not correct");
            hai = "haiphan";
            string dummy = hai >> 1;
            dummy = hai >> 1;
            Assert.AreEqual("iphanha", dummy, "Right Rotate is not correct");
        }

        [TestMethod]
        public void TestAssignment()
        {
            StrShift hai = new StrShift();
            hai = "Microsoft";
            string dummy = hai >> 1;
            dummy = hai << 1;
            Assert.AreEqual("Microsoft", dummy, "Assign is not correct");
            dummy = hai << 3;
            Assert.AreEqual("oftMicros", dummy, "Assign is not correct");
        }

        [TestMethod]
        public void TestIsEq()
        {
            StrShift hai = new StrShift();
            hai = "Microsoft";
            Assert.AreEqual(true, hai == "Microsoft", "IsEq is not correct");
            string dummy = hai >> 1;
            dummy = hai >> 2;
            Assert.AreEqual(false, hai == "Microsoft", "IsEq is not correct");
        }

        [TestMethod]
        public void TestIsNEq()
        {
            StrShift hai = new StrShift();
            hai = "Microsoft";
            Assert.AreEqual(false, hai != "Microsoft", "IsNEq is not correct");
            string dummy = hai >> 1;
            dummy = hai >> 2;
            Assert.AreEqual(false, hai != "rosoftMic", "IsNEq is not correct");
        }
    }
}
