using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Project_2
{
    public class aRandomNumberGenerator : Random
    {
        public readonly int Low;
        public readonly int High;

        /// <summary>
        /// Parameterized constructor uses the system clock to provide a seed value to instaniate a System.Random object
        /// </summary>
        /// <param name="lowest">inclusive lower bound</param>
        /// <param name="highest">exclusive upper bound</param>
        public aRandomNumberGenerator(int lowest, int highest) : base()
        {
            Low = lowest;
            High = highest - 1;
        }

        /// <summary>
        /// Parameterized constructor uses an explicit seed value to instaniate a System.Random object
        /// </summary>
        /// <param name="lowest">inclusive lower bound</param>
        /// <param name="highest">exclusive upper bound</param>
        /// <param name="seed">explicit seed value</param>
        public aRandomNumberGenerator(int lowest, int highest, int seed) : base(seed)
        {
            Low = lowest;
            High = highest - 1;
        }

        /// <summary>
        /// Overridden method to generate random integer from Low to High, inclusive
        /// </summary>
        /// <returns>random integer from Low to High, inclusive</returns>
        public override int Next()
        {
            return base.Next(Low, High + 1);
        }

        /// <summary>
        /// Overridden method to generate random integer from 0 to highest - 1
        /// </summary>
        /// <param name="highest">exclusive upper bound</param>
        /// <returns>returns random integer from 0 to highest - 1</returns>
        public override int Next(int highest)
        {
            return base.Next(highest);
        }
    }
}
