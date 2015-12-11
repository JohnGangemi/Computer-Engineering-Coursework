using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Project_2
{
    public class aGaussian : aRandomNumberGenerator
    {
        /// <summary>
        /// Generates random numbers from 6 to 36 inclusive
        /// </summary>
        public aGaussian() : base(6, 37)
        {
        }

        /// <summary>
        /// Generates random numbers from 6 to 36 inclusive provided a seed value
        /// </summary>
        /// <param name="seed"></param>
        public aGaussian(int seed) : base(6, 37, seed)
        {
        }
    }
}
