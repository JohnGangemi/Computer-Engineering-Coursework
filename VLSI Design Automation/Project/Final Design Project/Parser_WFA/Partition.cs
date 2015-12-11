using System.Collections.Generic;

namespace Parser_WFA
{
    public class Partition
    {
        int width;
        int length;
        int[] gateArray;
        List<string[]> inputs = new List<string[]>();
        List<string> outputs = new List<string>();

        public Partition(int _width, int _length, int[] _gates, List<string[]> _design_structs)
        {
            setWidth(_width);
            setLength(_length);
            setGates(_gates);
            setInputsAndOutputs(_design_structs);
        }

        private void setWidth(int _width)
        {
            width = _width;
        }

        private void setLength(int _length)
        {
            length = _length;
        }

        private void setGates(int[] _gates)
        {
            List<int> gateList = new List<int>();

            foreach (int gate in _gates)
            {
                gateList.Add(gate);
            }

            gateArray = gateList.ToArray();
        }

        private void setInputsAndOutputs(List<string[]> design_structs)
        {
            foreach (int gate_index in gateArray)
            {
                string[] gate = design_structs[gate_index];

                List<string> tmp_inputs = new List<string>();
                for (int i = 2; i < gate.Length - 1; i++)
                {
                    tmp_inputs.Add(gate[i]);
                }
                inputs.Add(tmp_inputs.ToArray());

                outputs.Add(gate[gate.Length - 1]);
            }
        }

        public int getWidth()
        { return width; }

        public int getLength()
        { return length; }

        public int getArea()
        { return width * length; }

        public int[] getGates()
        { return gateArray; }

        public List<string[]> getPartitionInputs()
        { return inputs; }

        public List<string> getPartitionOutputs()
        { return outputs; }
    }
}
