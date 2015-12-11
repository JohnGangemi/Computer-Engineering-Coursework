using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Project_2
{
    public class aCoin : aRandomNumberGenerator
    {
        /// <summary>
        /// Generates a random number from 0 to 1 inclusive
        /// </summary>
        public aCoin() : base(0, 2)
        {
        }

        /// <summary>
        /// Generates a random number from 0 to 1 inclusive provided a seed value
        /// </summary>
        /// <param name="seed"></param>
        public aCoin(int seed) : base(0, 2, seed)
        {
        }
    }
}
