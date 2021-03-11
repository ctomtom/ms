package rule;

import java.util.*;
import java.io.*;

public abstract class Variable {
String name ;
String value ;
int column ;

public Variable() {} ;
public Variable(String Name) {name = Name; value = null; }
void   setValue(String val) { value = val ; }
String getValue() { return value; }

// used by categorical only
Vector labels ;
void setLabels(String Labels) {
    labels = new Vector() ;
    StringTokenizer tok = new StringTokenizer(Labels," ") ;
    while (tok.hasMoreTokens()) {
         labels.addElement(new String(tok.nextToken())) ;
    }
}
// return the label with the specified index
String getLabel(int index) {
    return (String)labels.elementAt(index);
}

// return a string containing all labels
String getLabels() {
    String labelList = new String();
    Enumeration enum87 = labels.elements() ;
    while(enum87.hasMoreElements()) {
         labelList += enum87.nextElement() + " " ;
    }
    return labelList ;
}

// given a label, return its index
int getIndex(String label) {
    int i = 0, index = 0  ;
    Enumeration enum87 = labels.elements() ;
    while(enum87.hasMoreElements()) {
        if (label.equals(enum87.nextElement()))
        { index = i ; break ; }
        i++;
     }
     return i;
}


boolean categorical() { 
    if (labels != null) {
       return true ;
    } else {
       return false ; 
    }
}

// used by the DataSet class 
public void setColumn(int col) { column = col ; }
public abstract void computeStatistics(String inValue) ; 
public abstract int normalize(String inValue, float[] outArray, int inx);
public int normalizedSize() { return 1 ; }
public String getDecodedValue(float[] act, int index) { return String.valueOf(act[index]); }

}