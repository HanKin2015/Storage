开源的rapidxml_print.hpp文件需要修改，直接编译会报错函数未声明使用。

```
In file included from rapidxml_example.cpp:14:0:
rapidxml/rapidxml_print.hpp: In instantiation of ‘OutIt rapidxml::internal::print_node(OutIt, const rapidxml::xml_node<Ch>*, int, int) [with OutIt = std::back_insert_iterator<std::__cxx11::basic_string<char> >; Ch = char]’:
rapidxml/rapidxml_print.hpp:390:36:   required from ‘OutIt rapidxml::print(OutIt, const rapidxml::xml_node<Ch>&, int) [with OutIt = std::back_insert_iterator<std::__cxx11::basic_string<char> >; Ch = char]’
rapidxml_example.cpp:43:50:   required from here
rapidxml/rapidxml_print.hpp:115:37: error: ‘print_children’ was not declared in this scope, and no declarations were found by argument-dependent lookup at the point of instantiation [-fpermissive]
                 out = print_children(out, node, flags, indent);
                                     ^
rapidxml/rapidxml_print.hpp:169:22: note: ‘template<class OutIt, class Ch> OutIt rapidxml::internal::print_children(OutIt, const rapidxml::xml_node<Ch>*, int, int)’ declared here, later in the translation unit
         inline OutIt print_children(OutIt out, const xml_node<Ch> *node, int flags, int indent)
                      ^
rapidxml/rapidxml_print.hpp:120:41: error: ‘print_element_node’ was not declared in this scope, and no declarations were found by argument-dependent lookup at the point of instantiation [-fpermissive]
                 out = print_element_node(out, node, flags, indent);
                                         ^
```

调整函数使用顺序即可。
