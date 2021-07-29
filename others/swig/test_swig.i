%module test_swig
%{
    #define SWIG_WITH_INIT
    #include "test_swig.hpp"
%}
%include "test_swig.hpp"
