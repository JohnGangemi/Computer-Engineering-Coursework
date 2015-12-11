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
                width_remaining[i] = 0;
                for (int j = 0; j < slice_length; j++)
                {
                    slice_matrix[i, j] = 0;
                }
            }
            for (int i = 0; i < slice_length; i++)
            {
                length_remaining[i] = 0;
            }
        }

        //NEEDS WORK
        public void printSlice(int slice_width, int slice_length, string filename, int slice_number) 
        {
            using (StreamWriter outfile = File.AppendText(filename + @"\test.csv"))
            {
                string content = "Slice " + slice_number + "\n\n";
                for (int x = 0; x < slice_width; x++)
                {
                    //content += "[";
                    for (int y = 0; y < slice_length; y++)
                    {
                        //content += slice_matrix[x, y].ToString() + " ";
                        content += slice_matrix[x, y].ToString() + ",";
                    }
                    //content += "]\n";
                    content += "\n";
                }
                content += "\n\n";
                outfile.WriteLine(content);
            }
        }

        //Run this to put partition in slice.
        public Boolean fillSlice(int partition_width, int partition_length, int slice_width, int slice_length, int partition_number)
        {
            Boolean status = false;
            Boolean done = false;
            Boolean fit_h = false;
            Boolean fit_v = false;

            
            for (int i = 0; i < slice_length; i++)
            {
                for (int j = slice_width - 1; j >= 0; j--)
                {
                    if (j - partition_length >= 0 && i + partition_width < slice_length && slice_matrix[j,i] == 0 && !done)
                    {
                        for (int l = i; l < i + partition_width; l++)
                        {
                            for (int w = j; w > j - partition_length; w--)
                            {
                                if (slice_matrix[w,l] == 0)
                                {
                                    fit_v = true;
                                }
                                else
                                {
                                    status = false;
                                    fit_v = false;
                                }
                            }
                        }
                        done = true;
                    }
                    else if (j - partition_width >= 0 && i + partition_length < slice_length && slice_matrix[j, i] == 0 && !done)
                    {
                        for (int l = i; l < i + partition_length; l++)
                        {
                            for (int w = j; w > j - partition_width; w--)
                            {
                                if (slice_matrix[l,w] == 0)
                                {
                                    fit_h = true;
                                }
                                else
                                {
                                    status = false;
                                    fit_h = false;
                                }
                            }
                        }
                        done = true;
                    }
                    
                    
                    if ((fit_v || fit_h ) && done)
                    {
                        if (fit_h)
                        {
                          for (int l = i; l < i + partition_length; l++)
                            {
                                for (int w = j; w > j - partition_width; w--)
                                {
                                    slice_matrix[w, l] = partition_number + 1;
                                }
                            }

                            status = true;
                            return status;
                        }
                        if (fit_v)
                        {
                            for (int l = i; l < i + partition_width; l++)
                            {
                                for (int w = j; w > j - partition_length; w--)
                                {
                                    slice_matrix[w,l] = partition_number + 1;
                                }
                            }
                            status = true;
                            return status;
                        }
                    }
                    else
                    {
                        status = false;
                    }
                }
            }
                  
            return status;
        }

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
