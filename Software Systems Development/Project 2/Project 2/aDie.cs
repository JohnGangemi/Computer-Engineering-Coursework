using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Project_2
{
    public class aDie : aRandomNumberGenerator
    {
        /// <summary>
        /// Generates a random number from 1 to 6 inclusive
        /// </summary>
        public aDie() : base(1, 7)
        {
        }

        /// <summary>
        /// Generates a random number from 1 to 6 inclusive provided a seed value
        /// </summary>
        /// <param name="seed"></param>
        public aDie(int seed) : base(1, 7, seed)
        {
        }
    }
}
