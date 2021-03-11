package rule;

import java.awt.*;
import java.applet.*;
import java.util.* ;

public class RuleApplet extends Applet {
	public RuleApplet() {
		setEnabled(true);
		setBackground(new Color(230, 230, 250));
	}
    // user selected a rule base
    void choice1_Clicked() {
       String rbName = choice1.getSelectedItem() ;
       ///modif
       choice2.removeAll();       
       textArea1.setForeground(Color.BLUE);
       textArea2.setForeground(Color.BLUE);
       textArea3.setForeground(Color.BLUE);
       
       malade.reset() ;  // reset the rule base
       Enumeration vars = malade.variableList.elements() ;
       while (vars.hasMoreElements()) {
    	  /* if(((RuleVariable)vars.nextElement()).name.equals("Hypertension")==false
    			   &&((RuleVariable)vars.nextElement()).name.equals("Diagnostic")==false)
          */
            choice2.addItem(((RuleVariable)vars.nextElement()).name);}
        
      malade.displayVariables(textArea3) ;

	}

    // user selected a variable
    void choice2_Clicked(Event event) {
       String varName = choice2.getSelectedItem() ;
       choice3.removeAll() ;

       RuleVariable rvar = (RuleVariable)malade.variableList.get(varName);
       Enumeration labels = rvar.labels.elements();
       while (labels.hasMoreElements()) {
          choice3.addItem(((String)labels.nextElement())) ;
       }
	} 


    // user selected a value for a variable
	void choice3_Clicked(Event event) {
       String varName = choice2.getSelectedItem() ;
       String varValue = choice3.getSelectedItem() ;

       RuleVariable rvar = (RuleVariable)malade.variableList.get(varName);
       rvar.setValue(varValue) ;
       textArea3.appendText("\n" + rvar.name + " set to " + varValue) ;
       
	}

    // user pressed Find button -- do an infernece cycle
	void button1_Clicked(Event event) {
		 textArea2.setForeground(Color.BLUE);
	       textArea1.setForeground(Color.red);
	       textArea3.setForeground(Color.red);
       String goal = textField1.getText() ;
       //manylmodif
       
        
       malade.displayVariables(textArea2) ;
       if (radioButton1.getState() == true) { malade.forwardChain();}
	   if (radioButton2.getState() == true) {malade.backwardChain(goal);}
           
       malade.displayVariables(textArea2) ;
       
	}

	// user pressed Demo button -- do inference with pre-set values
	 

    void button3_Clicked(Event event) {

		//{{CONNECTION
		// Clear the text for TextArea
		textArea1.setText("");
		textArea2.setText("");
		textArea3.setText("");
		textArea1.setForeground(Color.blue);
		textArea3.setForeground(Color.blue);
		//}}

        /*currentRuleBase.reset() ;
        currentRuleBase.displayRules(textArea1);
        currentRuleBase.displayVariables(textArea3) ;*/
		malade.reset() ;
        malade.displayRules(textArea1);
        malade.displayVariables(textArea3) ;
    }

// display dialog to get user value for a variable
static public String waitForAnswer(String prompt, String labels) {

	// position dialog over parent dialog
    Point p = frame.getLocation() ;
    dlg = new RuleVarDialog(frame, true) ;
	dlg.label1.setText("   " + prompt + " (" + labels + ")");
    dlg.setLocation(400, 250) ;
    dlg.show() ;
    String ans = dlg.getText() ;
    return ans ;

}
	public void init() {
		super.init();
		//{{INIT_CONTROLS
		setLayout(null);
		addNotify();
		resize(624,527);
		button1 = new java.awt.Button("Find Goal");
		button1.reshape(228,468,108,30);
		add(button1);
		button3 = new java.awt.Button("Reset");
		button3.reshape(444,468,108,30);
		add(button3);
		textArea1 = new java.awt.TextArea();
		textArea1.reshape(12,48,312,144);
		textArea1.setBackground(new Color(240, 255, 240));
		add(textArea1);
		textArea2 = new java.awt.TextArea();
		textArea2.reshape(12,216,600,168);
		textArea2.setBackground(new Color(240, 255, 240));
		add(textArea2);
		label2 = new java.awt.Label("Trace Log");
		label2.reshape(24,192,168,24);
		add(label2);
		label1 = new java.awt.Label("Rule Base");
		label1.reshape(24,12,96,24);
		add(label1);
		choice1 = new java.awt.Choice();
		choice1.setBackground(new Color(245, 222, 179));
		add(choice1);
		choice1.reshape(132,12,192,24);
		Group1 = new CheckboxGroup();
		radioButton1 = new java.awt.Checkbox("Forward Chain", Group1, false);
		radioButton1.reshape(36,396,156,21);
		radioButton1.setBackground(new Color(220, 220, 220));
		add(radioButton1);
		choice3 = new java.awt.Choice();
		choice3.setBackground(new Color(245, 222, 179));
		add(choice3);
		choice3.reshape(480,36,135,24);
		label5 = new java.awt.Label("Value");
		label5.reshape(480,12,95,24);
		add(label5);
		choice2 = new java.awt.Choice();
		choice2.setBackground(new Color(245, 222, 179));
		add(choice2);
		choice2.reshape(336,36,137,24);
		textArea3 = new java.awt.TextArea();
		textArea3.reshape(336,72,276,122);
		textArea3.setBackground(new Color(240, 255, 240));
		add(textArea3);
		label4 = new java.awt.Label("Variable");
		label4.reshape(336,12,109,24);
		add(label4);
		radioButton2 = new java.awt.Checkbox("Backward Chain", Group1, false);
		radioButton2.reshape(36,420,156,24);
		radioButton2.setBackground(new Color(220, 220, 220));
		add(radioButton2);
                               
		textField1 = new java.awt.TextField();
		textField1.reshape(324,420,142,27);
		textField1.setBackground(new Color(240, 248, 255));
		add(textField1);
		label3 = new java.awt.Label("Goal");
		label3.reshape(324,384,80,30);
		add(label3);
		//}}

	 	frame = new Frame("Ask User") ;
	 	frame.resize(50,50) ;
	 	frame.setLocation(100,100) ; 	 	 
            
	 	choice1.addItem("Malade");

        malade = new RuleBase("malade") ;
	   malade.setDisplay(textArea2);
	   initmalade(malade);
        // initialize textAreas and list controls
        malade.displayRules(textArea1) ;
        
        malade.displayVariables(textArea3) ;
        radioButton1.setState(true) ;
        choice1_Clicked() ; // fill variable list
	}



	public boolean handleEvent(Event event) {
		if (event.target == button1 && event.id == Event.ACTION_EVENT) {
			button1_Clicked(event);
			return true;
		} 
		if (event.target == button3 && event.id == Event.ACTION_EVENT) {
			button3_Clicked(event);
			return true;
		}
		if (event.target == dlg && event.id == Event.ACTION_EVENT) {
			return dlg.handleEvent(event);
		}
	    if (event.target == choice1 && event.id == Event.ACTION_EVENT) {
			choice1_Clicked();
			return true;
	    }
	    if (event.target == choice2 && event.id == Event.ACTION_EVENT) {
			choice2_Clicked(event);
			return true;
	    }
	        if (event.target == choice3 && event.id == Event.ACTION_EVENT) {
			choice3_Clicked(event);
			return true;
	    }
		return super.handleEvent(event);
	}

	//{{DECLARE_CONTROLS
	java.awt.Button button1;
	java.awt.Button button2;
	java.awt.Button button3;
	java.awt.TextArea textArea1;
	java.awt.TextArea textArea2;
	java.awt.Label label2;
	java.awt.Label label1;
	java.awt.Choice choice1;
	java.awt.Checkbox radioButton1;
	CheckboxGroup Group1;
	java.awt.Choice choice3;
	java.awt.Label label5;
	java.awt.Choice choice2;
	java.awt.TextArea textArea3;
	java.awt.Label label4;
	java.awt.Checkbox radioButton2;
	///manyl modif
        //java.awt.Checkbox radioButton3;
	java.awt.TextField textField1;
	java.awt.Label label3;
	//}}

	static Frame frame ;
	static RuleVarDialog dlg ;
	 
    static RuleBase malade;
                                          
                                                                                                                   
                                                      
   public void initmalade(RuleBase rb)
    {
                                              rb.goalClauseStack = new Stack() ;
                                              rb.variableList = new Hashtable() ;
                                              
                                              RuleVariable diarhee = new RuleVariable("Diarhée") ;
                                              diarhee.setLabels("Oui Non");                                         
                                              rb.variableList.put(diarhee.name,diarhee) ;
                                              
                                              RuleVariable vomissement = new RuleVariable("Vomissement") ;
                                              vomissement.setLabels("Oui Non");                                         
                                              rb.variableList.put(vomissement.name,vomissement) ;
                                              
											  RuleVariable ictere = new RuleVariable("Ictère") ;
                                              ictere.setLabels("Oui Non");                                         
                                              rb.variableList.put(ictere.name,ictere) ;
                                              
                                              RuleVariable fievre = new RuleVariable("Fièvre") ;
                                              fievre.setLabels("Oui Non");                                           
                                              rb.variableList.put(fievre.name,fievre) ;
											  
                                              RuleVariable douleurabdominale = new RuleVariable("Douleur abdominale");
                                              douleurabdominale.setLabels("Oui Non");                                         
                                              rb.variableList.put(douleurabdominale.name,douleurabdominale) ;

											                                                
                                              RuleVariable sellesdecolorees = new RuleVariable("Selles décolorées");
                                              sellesdecolorees.setLabels("Oui Non");                                         
                                              rb.variableList.put(sellesdecolorees.name,sellesdecolorees) ;
                                              
                                              RuleVariable urinesfoncees = new RuleVariable("Urines foncées") ;
                                              urinesfoncees.setLabels("Oui Non");								
                                              rb.variableList.put(urinesfoncees.name,urinesfoncees) ;									  											  
							                   
											  
											  RuleVariable ventredebois = new RuleVariable("Ventre de bois") ;
											  ventredebois.setLabels("Oui Non");                                          
                                              rb.variableList.put(ventredebois.name,ventredebois) ;
											  
                                              RuleVariable mauxdetete = new RuleVariable("Maux de tête") ;
                                              mauxdetete.setLabels("Oui Non");                                           
                                              rb.variableList.put(mauxdetete.name,mauxdetete) ;
                                              
                                              RuleVariable rhinorrhee = new RuleVariable("Rhinorrhee") ;
                                              rhinorrhee.setLabels("Oui Non");                                           
                                              rb.variableList.put(rhinorrhee.name,rhinorrhee) ;
                                              
                                              RuleVariable courbatures = new RuleVariable("Courbatures") ;
                                              courbatures.setLabels("Oui Non");                                           
                                              rb.variableList.put(courbatures.name,courbatures);
                                              
                                              RuleVariable diagnostic=new RuleVariable("Diagnostic");                                                                                        
                                              rb.variableList.put(diagnostic.name,diagnostic);
                                              
                                              RuleVariable pressionalterielle=new RuleVariable("Pression altérielle");
                                              pressionalterielle.setLabels("8 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24");
                                              rb.variableList.put(pressionalterielle.name, pressionalterielle);
                                              
                                              
                                              RuleVariable temperature=new RuleVariable("Température");
                                              temperature.setLabels("37 38 39 40 41 42");
                                              rb.variableList.put(temperature.name, temperature);
                                            
                                              RuleVariable hypertension=new RuleVariable("Hypertension");
                                              rb.variableList.put(hypertension.name, hypertension);
                                              hypertension.setLabels("Oui Non");
                                              
                                              RuleVariable paralysiehemicorps=new RuleVariable("Paralysie hemicorps");
                                              paralysiehemicorps.setLabels("Oui Non");
                                              rb.variableList.put(paralysiehemicorps.name, paralysiehemicorps);
                                              
                                              // Note: at this point all variables values are NULL
                                               
                                              Condition cEquals = new Condition("=") ;
                                              Condition cNotEquals = new Condition("!=") ;
                                              Condition cLessThan = new Condition("<") ;
                                              Condition cMoreThan = new Condition(">") ;
                                              
                                           // define rules
                                              rb.ruleList = new Vector() ;
                                                                                          
                                                 Rule avc=new Rule(rb,"AVC",
                                                        new Clause(hypertension, cEquals, "Oui"),                                                      
                                                        new Clause(paralysiehemicorps, cEquals, "Oui"),  
                                                        new Clause(diagnostic,cEquals,"AVC"));
                                                
                                                 Rule hypertens=new Rule(rb,"Hypertension",
                                                        new Clause(pressionalterielle, cMoreThan, "13"),                                                      
                                                        new Clause(hypertension, cEquals, "Oui"));   
                                                 
                                                 Rule fiev=new Rule(rb,"Fievre",
                                                         new Clause(temperature, cMoreThan, "37"),                                                      
                                                         new Clause(fievre, cEquals, "Oui")); 
                                                 
                                                 Rule colongite = new Rule(rb, "Colongite" ,
                                                       
                                                      new Clause(ictere,cEquals,"Oui")  ,
                                                      new Clause(fievre, cEquals, "Oui"),
                                                      new Clause(douleurabdominale,cEquals,"Oui"),
                                                      new Clause(diagnostic,cEquals,"Colongite"));
                                              
                                                 Rule cholestases = new Rule(rb, "Cholestases",                                                      
                                                      new Clause(ictere,cEquals,"Oui") ,
                                                      new Clause(sellesdecolorees, cEquals, "Oui"),
                                                      new Clause(urinesfoncees,cEquals,"Oui"),
                                                      new Clause(diagnostic,cEquals,"Cholestases"));
                                              
                                                 Rule peritonite = new Rule(rb, "Peritonite",                                                      
                                                     new Clause(fievre,cEquals,"Oui"),
                                                     new Clause(douleurabdominale,cEquals,"Oui"),
                                                     new Clause(ventredebois,cEquals,"Oui"),
                                                     new Clause(diagnostic,cEquals,"Peritonite"));
                                               
                                                 Rule grippe = new Rule(rb,"Grippe" ,                             		
                                                	  new Clause(fievre,cEquals,"Oui"),                                                                                                                      
                                                      new Clause(mauxdetete, cEquals, "Oui"),                                                     
                                                      new Clause(rhinorrhee, cEquals, "Oui"),
                                                      new Clause(courbatures, cEquals, "Oui"),
                                                      new Clause(diagnostic,cEquals,"Grippe"));                                              
                                                 
                                                 Rule intoxication = new Rule(rb, "Intoxication",                                                               
                                                   	  new Clause(fievre, cEquals, "Oui"),                                                      
                                                         new Clause(diarhee, cEquals, "Oui"),
                                                         new Clause(vomissement, cEquals, "Oui"),
                                                         new Clause(diagnostic,cEquals,"Intoxication"));
                                                 
                                                 
                                                 Rule rhume = new Rule(rb, "Rhume",                                                               
                                                   	          new Clause(mauxdetete, cEquals, "Oui"),                                                      
                                                              new Clause(rhinorrhee, cEquals, "Oui"),
                                                              new Clause(diagnostic,cEquals,"Rhume"));                                                                   
                                                   
                                                                   }

}
