Compile code with the following command:
g++ Main.cpp Graph.cpp Edge.cpp -o longestPath

Run the program with the following command:
./longestPath <input_file_path>

Output is saved in the current working directory to output.txt

Notes...
<input_file_path> requires a file location on disk.
If the input file pah includes spaces, surround with quotes.

Examples...
If the input file path is not in the same directory as longestPath
./longestPath c:\...\input.txt
./longestPath "c:\...\ input with space.txt"

If the input file path is in the same directory as longestPath
./longestPath input.txt
./longestPath "input with space.txt"
