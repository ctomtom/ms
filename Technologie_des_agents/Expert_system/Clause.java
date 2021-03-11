package rule;

import java.util.*;
import java.io.*;


public class Clause {
Vector ruleRefs ;
RuleVariable lhs ;
String rhs ;
Condition cond ;
Boolean consequent ; // true or false
Boolean truth;      // states = null(unknown), true or false

Clause(RuleVariable Lhs, Condition Cond, String Rhs)
{
lhs = Lhs ;	cond = Cond ; rhs = Rhs ;
lhs.addClauseRef(this) ;
ruleRefs = new Vector() ;
truth = null ;
consequent = new Boolean(false) ;
}
public String toString(){
    return lhs.name + cond.toString() + rhs +" ";
}
//to register the rule with this clause
void addRuleRef(Rule ref) { ruleRefs.addElement(ref);}

Boolean check() {
if (consequent.booleanValue() == true) return null ;
if (lhs.value == null) {
return truth = null ;    // Var value is undefined
} else {

	Double lhsNumericValue = null ;
    Double rhsNumericValue = null;
    boolean bothNumeric = true ;
    try{
        lhsNumericValue = Double.valueOf(lhs.value);
        rhsNumericValue = Double.valueOf(rhs);
    }catch(Exception e){
        bothNumeric = false;
    }
    switch(cond.index) {
    case 1:
        if(bothNumeric){
            truth = new Boolean(lhsNumericValue.compareTo(rhsNumericValue)==0);
        }else{
            truth = new Boolean(lhs.value.equalsIgnoreCase(rhs));
        }
    break;
    case 2:
        if(bothNumeric){
            truth = new Boolean(lhsNumericValue.compareTo(rhsNumericValue)>0);
        }else{
            truth = new Boolean(lhs.value.equalsIgnoreCase(rhs));
        }
    break;
    case 3: 
        if(bothNumeric){
            truth = new Boolean(lhsNumericValue.compareTo(rhsNumericValue)<0);
        }else{
            truth = new Boolean(lhs.value.equalsIgnoreCase(rhs));
        }
    break;           
    case 4:
        if(bothNumeric){
            truth = new Boolean(lhsNumericValue.compareTo(rhsNumericValue)!=0);
        }else{
            truth = new Boolean(lhs.value.equalsIgnoreCase(rhs));
        }
    break;
    }
return truth ;}
}
void isConsequent() { consequent = new Boolean(true); }
Rule getRule() {
if (consequent.booleanValue() == true) {return (Rule)ruleRefs.firstElement();}
else {return null ;}}
};