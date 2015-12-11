using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace Parser_WFA
{
    public class Slice
    {
        int[] gates_array;
        int[] inputs_array;
        int[] outputs_array;
        int[] connections_array;
        //int slice_width;
       // int slice_length;
        int[,] slice_matrix;
        int[] width_remaining;
        int[] length_remaining;

        /*public Slice(int[] gateList, int[] input_array, int[] output_array, int[] connection_array, int slice_width, int slice_length)
        {
            setGates(gateList);
            setInputs(input_array);
            setOutputs(output_array);
            setConnections(connection_array);
            createSliceMatrix(slice_width, slice_length);
        }*/

        public Slice(int slice_width, int slice_length)
        {
            width_remaining = new int[slice_width];
            length_remaining = new int[slice_length];
            createSliceMatrix(slice_width, slice_length);
        }

        public void setGates(int[] gateList)
        {
            List<int> gates = new List<int>();

            foreach (int gate in gates)
            {
                gates[gate] = gateList[gate];
            }

            gates_array = gates.ToArray();
        }

        public void setInputs(int[] inputList)
        {
            List<int> inputs = new List<int>();

            foreach (int index in inputList)
            {
                inputs[index] = inputList[index];
            }

            inputs_array = inputs.ToArray();
        }

        public void setOutputs(int[] outputList)
        {
            List<int> outputs = new List<int>();

            foreach (int index in outputList)
            {
                outputs[index] = outputList[index];
            }

            outputs_array = outputs.ToArray();
        }

        public void setConnections(int[] connectionList)
        {
            List<int> connections = new List<int>();

            foreach (int index in connectionList)
            {
                connections[index] = connectionList[index];
            }

            connections_array = connections.ToArray();
        }

        public void createSliceMatrix(int slice_width, int slice_length)
        {
            //Make 2d array for your slice
            //first index is width, second is length
            slice_matrix = new int[slice_width, slice_length];

            for (int i = 0; i < slice_width; i++)
            {
                width_remaining[i] = slice_width;
                for (int j = 0; j < slice_length; j++)
                {
                    slice_matrix[i, j] = 0;
                }
            }
            for (int i = 0; i < slice_length; i++)
            {
                length_remaining[i] = slice_length;
            }
        }

        //NEEDS WORK
        public void printSlice(int slice_width, int slice_length) 
        {
            using (StreamWriter outfile = new StreamWriter(@"G:\Users\Steven\Desktop\test.csv"))
            {
                for (int x = 0; x < slice_width; x++)
                {
                    string content = "[";
                    for (int y = 0; y < slice_length; y++)
                    {
                        content += slice_matrix[x, y].ToString() + " ";
                    }
                    content += "]";
                    outfile.WriteLine(content);
                }
            }

            /*for (int i = 0; i < slice_width; i++)
            {
                for (int j = 0; j < slice_length; j++)
                {
                    Console.Write(string.Format("{0} ", slice_matrix[i, j]));
                }
                Console.Write(Environment.NewLine + Environment.NewLine);
            }
            Console.ReadLine();*/
        }


        //Run this to put partition in slice.
        public Boolean fillSlice(int partition_width, int partition_length, int slice_width, int slice_length, int partition_number)
        {
            Boolean status = true;
            Boolean done = false;

            for (int i = 0; i < slice_length; i++)
            {
                for (int j = slice_width - 1; j >= 0; j--)
                {
                    if (slice_matrix[i, j] == 0 && length_remaining[j] >= partition_width && width_remaining[i] >= partition_length && !done) //Rotated
                    {
                        for (int g = i; g < partition_width; g++)
                        {
                            for (int k = j; k > j - partition_length; k--)
                            {
                                slice_matrix[g, k] = partition_number + 1;
                            }
                        }
                        for (int l = i; l < partition_width; l++)
                        {
                            width_remaining[l] -= partition_length;
                        }
                        for (int w = j; w > j - partition_length; w--)
                        {
                            length_remaining[w] -= partition_width;
                        }
                        done = true;
                    }
                    else if (slice_matrix[i, j] == 0 && length_remaining[j] >= partition_length && width_remaining[i] >= partition_width && !done) //Original
                    {
                        for (int g = i; g < (partition_length + i); g++)
                        {
                            for (int k = width_remaining[i]-1; k > width_remaining[i] - partition_width; k--)
                            {
                                slice_matrix[g, k] = partition_number + 1;
                            }
                        }

                        for (int w = width_remaining[i]; w > width_remaining[i] - partition_width; w--)
                        {
                            length_remaining[w] -= partition_length;
                        }
                        for (int l = i; l < partition_length + i; l++)
                        {
                            width_remaining[l] -= partition_width;
                        }
                        done = true;
                    }
                    else if (i == slice_length - 1 && j == 0 && !done)
                    {
                        status = false;
                    }
                }
            }
                return status;
        }
       /* public Boolean fillSlice(int partition_width, int partition_length, int slice_width, int slice_length, int partition_number)
        {
            Boolean status = false;
            for (int j = 0; j < slice_length - 1; j++)
            {
                for (int i = slice_width - 1; i > 0; i--)
                {
                    if (slice_matrix[i, j] == 0 && partition_width < width_remaining[j] && partition_length < length_remaining[i])
                    {
                        for (int g = i; g > i - partition_width; g--)
                        {
                            for (int k = j; k < partition_length - 1; k++)
                            {
                                slice_matrix[g, k] = partition_number + 1;
                            }
                        }

                        for (int k = i - 1; k > i - partition_length; k++)
                        {
                            length_remaining[k] -= partition_length;
                        }

                        for (int k = j; k >= partition_width; k--)
                        {
                            width_remaining[k] -= partition_width;
                        }
                        status = true;
                        return status;
                    }
                    else if (slice_matrix[i, j] == 0 && partition_width < length_remaining[i] && partition_length < width_remaining[j])
                    {
                        for (int g = j; g < partition_length - 1; g++)
                        {
                            for (int k = i; k > i - partition_width; k--)
                            {
                                slice_matrix[g, k] = partition_number + 1;
                            }
                        }

                        for (int k = j; k < partition_length; k++)
                        {
                            length_remaining[k] -= partition_width;
                        }

                        for (int k = i - 1; k >= partition_width; k--)
                        {
                            width_remaining[k] -= partition_length;
                        }
                        status = true;
                        return status;
                    }
                    else
                    {
                        status = false;
                    }
                }
            }
            return status;
        }*/
       /* public Boolean fillSlice(int partition_width, int partition_length, int slice_width, int slice_length, int partition_number)
        {
            Boolean status = true;
            Boolean written = false;
           // int start_write_width = 0; //Which width co-ordinate to start the write from, so if this = 30, start at index 30 of matrix and go down whatever partition_width is.
           // int start_write_length = 0; //Which length co-ordinate to start the write from, so if this = 30, start at index 30 of matrix and go down whatever patrition_length is.
            for(int i = 0; i < slice_length; i++)
            {
                for (int j = slice_width - 1; j >= 0; j--) //Width and Length switched due to filling bottom left upward/ outward
                {
                    if (!written) 
                    {
                        if ((partition_width < width_remaining[i]) && partition_length < length_remaining[j] && slice_matrix[j, i] == 0) //Original orientation
                        //if(j > width_remaining[i] && i > length_remaining[j] && slice_matrix[j, i] == 0)
                        {
                            for (int k = i; k <= i + partition_length; k++)
                            {
                                for (int g = j; g >= j - partition_width; g--)
                                {
                                    written = true;
                                    slice_matrix[g, k] = partition_number + 1;
                                }
                            }

                            for (int k = j; k > (j - partition_width); k--)
                            {
                                length_remaining[k] -= partition_length;
                            }

                            for (int k = i; k <= partition_length; k++)
                            {
                                width_remaining[k] -= partition_width;
                            }

                            return status;
                        }
                        else if (partition_width < length_remaining[j] && partition_length < width_remaining[i] && slice_matrix[j, i] == 0) //Rotated orientation
                        //else if(i > width_remaining[i] && j > length_remaining[j] && slice_matrix[j, i] == 0)
                        {
                            //Check to make sure the entire partition will fit in slice
                            for (int k = j; k >= i - partition_width; k++)
                            {
                                for (int g = i; g <= j + partition_length; g++)
                                {
                                    written = true;
                                    slice_matrix[k, g] = partition_number + 1;
                                }
                            }

                            for (int k = j; k < (j - partition_width); k--)
                            {
                                length_remaining[k] -= partition_length; 
                            }

                            for (int k = i; k <= partition_length; k++)
                            {
                                width_remaining[k] -= partition_length;
                            }
                            return status; 
                        }
                        else if ((i == slice_length - 1 && j == 0) && !written)
                        {
                            return false;
                        }
                    }
                }
            }

            return false;
        }*/

        public int[] getGates()
        { 
            return gates_array;
        }

        public int[] getInputs()
        {
            return inputs_array;
        }

        public int[] getOutputs()
        {
            return outputs_array;
        }

        public int[] getConnections()
        {
            return connections_array;
        }
    
    }
}
