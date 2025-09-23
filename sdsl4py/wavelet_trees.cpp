#ifndef WAVELET_TREES_CPP
#define WAVELET_TREES_CPP

#include <pybind11/pybind11.h>
#include <sdsl/wavelet_trees.hpp>
#include <sdsl/vectors.hpp>

namespace py = pybind11;

using sdsl::wt_int;
using sdsl::wt_huff;
using sdsl::wt_huff_int;
using sdsl::wt_gmr;

// Helper function to add wavelet tree classes to the Python module
template <typename T>
void add_wavelet_tree(py::module &m, const char* name) {
    py::class_<T>(m, name)
        .def(py::init<>(), R"pbdoc(
            Default constructor for wavelet tree.
        )pbdoc")
        .def("access", [](const T& wt, size_t idx) { return wt[idx]; }, py::arg("idx"), R"pbdoc(
            Accesses the element at the given position.
            Args:
                idx (size_t): Index of the element to access.
            Returns:
                The value at the given index.
        )pbdoc")
        .def("rank", [](const T& wt, size_t idx, int symbol) { return wt.rank(idx, symbol); }, py::arg("idx"), py::arg("symbol"), R"pbdoc(
            Returns the number of occurrences of a symbol up to the given index.
            Args:
                idx (size_t): Index up to which the symbol count is calculated.
                symbol (int): Symbol for which to calculate the rank.
            Returns:
                Number of occurrences of the symbol.
        )pbdoc")
        .def("select", [](const T& wt, size_t idx, int symbol) { return wt.select(idx, symbol); }, py::arg("idx"), py::arg("symbol"), R"pbdoc(
            Returns the position of the i-th occurrence of the symbol.
            Args:
                idx (size_t): The index of the occurrence.
                symbol (int): Symbol for which to calculate the select.
            Returns:
                The position of the occurrence.
        )pbdoc")
        .def("size_in_bytes", [](const T& wt) { return sdsl::size_in_bytes(wt); }, R"pbdoc(
            Returns the size of the wavelet tree in bytes.
        )pbdoc")
        .def("size_in_mega_bytes", [](const T& wt) { return sdsl::size_in_mega_bytes(wt); }, R"pbdoc(
            Returns the size of the wavelet tree in megabytes.
        )pbdoc")
        .def("store_to_file", [](const T& wt, const std::string& file) { return sdsl::store_to_file(wt, file); }, py::arg("file"), R"pbdoc(
            Stores the wavelet tree to a file.
            Args:
                file (str): The name of the file to store the tree.
        )pbdoc")
        .def("load_from_file", [](T& wt, const std::string& file) { return sdsl::load_from_file(wt, file); }, py::arg("file"), R"pbdoc(
            Loads the wavelet tree from a file.
            Args:
                file (str): The name of the file to load the tree from.
        )pbdoc")
        .def("construct0", [](T& wt, const std::string& file) { return
	      sdsl::construct(wt, file, 0); }, R"pbdoc(
            Construct the wavelet tree from a serialized input file.
        )pbdoc")
        .def("construct1", [](T& wt, const std::string& file) { return
	    sdsl::construct(wt, file, 1); }, R"pbdoc(
            Construct the wavelet tree from a file with 1-byte symbols.
        )pbdoc");
}

// Helper function to add wavelet tree classes to the Python module (with support to 2D queries)
template <typename T>
void add_wavelet_tree2D(py::module &m, const char* name) {
    py::class_<T>(m, name)
        .def(py::init<>(), R"pbdoc(
            Default constructor for wavelet tree.
        )pbdoc")
        .def("access", [](const T& wt, size_t idx) { return wt[idx]; }, py::arg("idx"), R"pbdoc(
            Accesses the element at the given position.
            Args:
                idx (size_t): Index of the element to access.
            Returns:
                The value at the given index.
        )pbdoc")
        .def("rank", [](const T& wt, size_t idx, int symbol) { return wt.rank(idx, symbol); }, py::arg("idx"), py::arg("symbol"), R"pbdoc(
            Returns the number of occurrences of a symbol up to the given index.
            Args:
                idx (size_t): Index up to which the symbol count is calculated.
                symbol (int): Symbol for which to calculate the rank.
            Returns:
                Number of occurrences of the symbol.
        )pbdoc")
        .def("select", [](const T& wt, size_t idx, int symbol) { return wt.select(idx, symbol); }, py::arg("idx"), py::arg("symbol"), R"pbdoc(
            Returns the position of the i-th occurrence of the symbol.
            Args:
                idx (size_t): The index of the occurrence.
                symbol (int): Symbol for which to calculate the select.
            Returns:
                The position of the occurrence.
        )pbdoc")
        .def("range_search_2d", [](const T& wt, size_t x_start, size_t x_end ,size_t y_start, size_t y_end,bool report=true ) { return wt.range_search_2d(x_start, x_end, y_start, y_end, report);
        }, py::arg("x_start"), py::arg("x_end"), py::arg("y_start"), py::arg("y_end"),py::arg("report") = true, R"pbdoc(
            Performs a 2D range search on the wavelet tree.
            Args:
                x_start (size_t): Start of the x-range (index range).
                x_end (size_t): End of the x-range (index range).
                y_start (int): Start of the y-range (value range).
                y_end (int): End of the y-range (value range).
            Returns:
                List of (position, value) pairs that fall within the specified range.
        )pbdoc")
        .def("size_in_bytes", [](const T& wt) { return sdsl::size_in_bytes(wt); }, R"pbdoc(
            Returns the size of the wavelet tree in bytes.
        )pbdoc")
        .def("size_in_mega_bytes", [](const T& wt) { return sdsl::size_in_mega_bytes(wt); }, R"pbdoc(
            Returns the size of the wavelet tree in megabytes.
        )pbdoc")
        .def("store_to_file", [](const T& wt, const std::string& file) { return sdsl::store_to_file(wt, file); }, py::arg("file"), R"pbdoc(
            Stores the wavelet tree to a file.
            Args:
                file (str): The name of the file to store the tree.
        )pbdoc")
        .def("load_from_file", [](T& wt, const std::string& file) { return sdsl::load_from_file(wt, file); }, py::arg("file"), R"pbdoc(
            Loads the wavelet tree from a file.
            Args:
                file (str): The name of the file to load the tree from.
        )pbdoc")
        .def("construct", [](T& wt, const std::string& file, int type) {
	         if (type == 0 || type == 1) {
	             sdsl::construct(wt, file, type);
	         } 
	         else{ 
	         	throw std::invalid_argument("Invalid type: must be 0 or 1");
	         }
	     }, R"pbdoc(
	         Construct the wavelet tree from a serialized input file (type = 0)
	         or from a file with 1-byte symbols (type = 1).
	     )pbdoc");
}


#endif // WAVELET_TREES_CPP
