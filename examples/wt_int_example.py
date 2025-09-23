import sdsl4py

# Create a wavelet tree wt_int from this Python file
wt = sdsl4py.WaveletTreeInt()
wt.construct("wt_int_example.py", 1)

# Get the size in bytes
print("Size in bytes:", wt.size_in_bytes())


# Count how many occurrences of the 's' symbols there are in the 14 first
# symbols "import sdsl4py"
print("rank(wt, 13, 's'):", wt.rank(13, ord('s')))

# Get the position of the first 's' in the 14 first symbols "import sdsl4py" 
print("select(wt, 1, 's'):", wt.select(1, ord('s')))
# Get the position of the second 's' in the 14 first symbols "import sdsl4py"
print("select(wt, 2, 's'):", wt.select(2, ord('s')))

# Store the wavelet tree to a file
wt.store_to_file("output.wt_int")

# Load the wavelet tree from a file
wt2 = sdsl4py.WaveletTreeInt()
wt2.load_from_file("output.wt_int")

# Run a 2D range query. In this case, counting how many occurrences of the
# symbols 's', 't' or 'u' there are  in the 14 first symbols "import sdsl4py"
results = wt2.range_search_2d(0, 13, 115, 117)
print(results)
