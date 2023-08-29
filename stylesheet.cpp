#include "stylesheet.h"

std::string styleSheet_build()
{
    std::string strylestr = "";
    strylestr += "\n<style>\n";

    strylestr += " thead {\n  ";
    strylestr += "    background: white;\n  ";
    strylestr += "   position: sticky;\n  ";
    strylestr += "   top: 0;";
    strylestr += "   box-shadow: 0 2px 2px -1px rgba(0, 0, 0, 0.4);\n  ";
    strylestr += " }\n  ";

    strylestr += "#table-parent \n  ";
    strylestr += "{ \n  ";
    strylestr += "  height:75vh; \n  ";
    strylestr += "  overflow:scroll; \n  ";
    strylestr += "   border-radius :10px; \n  ";
    strylestr += "    border: 1px solid grey; \n  ";
    strylestr += "    width:99%; \n  ";
    strylestr += "} \n  ";
    strylestr += " \n  ";
    strylestr += "table{ \n  ";
    strylestr += " width : 100%; \n  ";
    strylestr += " overflow:scroll; \n  ";
    strylestr += "} \n  ";
    strylestr += " \n  ";
    strylestr += " \n  ";
    strylestr += "table, td { \n  ";
    strylestr += "  border: 1px solid black; \n  ";
    strylestr += "  border-collapse: collapse; \n  ";
    strylestr += "  word-wrap:break-word; \n  ";
    strylestr += "} \n  ";
    strylestr += " \n  ";
    strylestr += "th{ \n  ";
    strylestr += "  background-color:white; \n  ";
    strylestr += "  color:black; \n  ";
    strylestr += "  font-weight:bold; \n  ";
    strylestr += "  border: 1px solid black; \n  ";
    strylestr += "  border-collapse: collapse; \n  ";
    strylestr += "} \n  ";


    strylestr += "textarea { \n  ";
    strylestr += "  background-color:white; \n  ";
    strylestr += "  width:99%; \n  ";

    strylestr += "} \n  ";

    strylestr += " .pagination { ";
    strylestr += "  display: inline-block; } ";

    strylestr += " .pagination button { ";
    strylestr += "  color: black;";
    strylestr += "  float: left;  padding: 5px 5px;";
    strylestr += "  text-decoration: none; }\n";

strylestr += " button:hover { ";
 strylestr += " background-color: green;";
 strylestr += " border-radius: 10x; }";

    strylestr += "\n</style>\n";

    return strylestr;
}

