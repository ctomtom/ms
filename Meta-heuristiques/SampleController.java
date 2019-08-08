package application;

import java.net.URL;
import java.util.ArrayList;
import java.util.ResourceBundle;

import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.chart.BarChart;
import javafx.scene.chart.CategoryAxis;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.TextArea;

public class SampleController implements Initializable {
	App app=new App();
@FXML ChoiceBox<String> algo=new ChoiceBox<String>();
@FXML ChoiceBox<String> esprech=new ChoiceBox<String>();
@FXML ChoiceBox<String> instance=new ChoiceBox<String>();
@FXML TextArea clauses=new TextArea();
@FXML TextArea solution=new TextArea();
@FXML TextArea param=new TextArea();
@FXML CategoryAxis x;
@FXML NumberAxis y;

@FXML BarChart<?,?> graphe;
XYChart.Series s=new XYChart.Series<>();
String inst; int fitness; int plg; int t;
	@Override
	public void initialize(URL arg0, ResourceBundle arg1) {
	
		
	algo.getItems().add("BFS");
	algo.getItems().add("DFS");
	algo.getItems().add("AG");
	algo.getItems().add("PSO");
	esprech.getItems().add("u20");
	esprech.getItems().add("u50");
	esprech.getItems().add("u75");
	//instance.setValue("");
	esprech.getSelectionModel().selectedIndexProperty().addListener(
	  ( ov, oldVal, newVal ) -> {
         
          // change second ChoiceBox values
         int optionSelected = newVal.intValue(); 
  
	if(optionSelected==0)
	{instance.getItems().clear();
		instance.getItems().add("uf20-01");
	instance.getItems().add("uf20-02");
	instance.getItems().add("uf20-03");
	instance.getItems().add("uf20-04");
	instance.getItems().add("uf20-05");
	instance.getItems().add("uf20-06");
	instance.getItems().add("uf20-07");
	instance.getItems().add("uf20-08");
	instance.getItems().add("uf20-09");
	instance.getItems().add("uf20-010");}
	else 
		{ if(optionSelected==1)
	{
			instance.getItems().clear();
	instance.getItems().add("uf50-01");
	instance.getItems().add("uf50-02");
	instance.getItems().add("uf50-03");
	instance.getItems().add("uf50-04");
	instance.getItems().add("uf50-05");
	instance.getItems().add("uf50-06");
	instance.getItems().add("uf50-07");
	instance.getItems().add("uf50-08");
	instance.getItems().add("uf50-09");
	instance.getItems().add("uf50-010");
	}
	else { if(optionSelected==2)
	{instance.getItems().clear();
		instance.getItems().add("uf75-01");
	instance.getItems().add("uf75-02");
	instance.getItems().add("uf75-03");
	instance.getItems().add("uf75-04");
	instance.getItems().add("uf75-05");
	instance.getItems().add("uf75-06");
	instance.getItems().add("uf75-07");
	instance.getItems().add("uf75-08");
	instance.getItems().add("uf75-09");
	instance.getItems().add("uf75-010");
	}}}}
	);}
	
	@SuppressWarnings("unchecked")
	public void execution() {
		clauses.clear();
		app.setCol(3);
		solution.clear();
		param.clear();
		if(esprech.getSelectionModel().getSelectedIndex()==0) {app.setLigne(91);plg=20;t=30000;}
		if(esprech.getSelectionModel().getSelectedIndex()==1) {app.setLigne(218);plg=50;t=60000;}
		if(esprech.getSelectionModel().getSelectedIndex()==2) {app.setLigne(325);plg=75;t=180000;}
		inst=instance.getSelectionModel().getSelectedItem();
		System.out.print(inst);
		app.remplir("C:\\Users\\khadidja\\Desktop\\SII\\S2\\mh\\"+inst+".cnf");	
	
        for(int i=0;i<app.ligne;i++)
        {
        for(int j=0;j<app.getCol();j++)
        {clauses.appendText(app.m[i][j]+" ");} 
        clauses.appendText("\n");
        }
        
        if(algo.getSelectionModel().getSelectedIndex()==0) {
        	if(plg==20) {param.appendText("Temps="+30+"s\n");}
        	if(plg==50) {param.appendText("Temps="+60+"s\n");}
        	ArrayList<Noeud>sol=app.bfs(plg,t);
        	Noeud n = new Noeud();fitness=n.sat(app.m,sol,3);
        for(int j=0;j<sol.size();j++)
        {solution.appendText(sol.get(j).getValue()+" ");} 
        
        int in=instance.getSelectionModel().getSelectedIndex();
        s.getData().add(new XYChart.Data(""+in,fitness));
        graphe.getData().addAll(s);
        }
        
        if(algo.getSelectionModel().getSelectedIndex()==1) {
        	if(plg==20) {param.appendText("Temps="+30+"s\n");}
        	if(plg==50) {param.appendText("Temps="+60+"s\n");}
        	param.appendText("Profondeur maximal="+plg);
        	ArrayList<Noeud>sol=app.dfs(plg,t);Noeud n = new Noeud();
        	fitness=n.sat(app.m,sol,3);
        for(int j=0;j<sol.size();j++)
        {solution.appendText(sol.get(j).getValue()+" ");} 
        int in=instance.getSelectionModel().getSelectedIndex();
        s.getData().add(new XYChart.Data(""+in,fitness));
        graphe.getData().addAll(s);
        }
        
        if(algo.getSelectionModel().getSelectedIndex()==2) {
        	param.appendText("maxiter=10 \n");
        	param.appendText("rc=0.1\n");
        	param.appendText("mr=0.3\n");
        	param.appendText("popsize=50");
        	
        Solution sol=app.algogenetique(plg);fitness=sol.getFitness();
        for(int j=0;j<sol.getBits().size();j++)
        {solution.appendText(sol.getBits().get(j)+" ");} 
        int in=instance.getSelectionModel().getSelectedIndex();
        s.getData().add(new XYChart.Data(""+in,fitness));
        graphe.getData().addAll(s);
        }
        
        if(algo.getSelectionModel().getSelectedIndex()==3) {
        	param.appendText("maxiter=70 \n");
        	param.appendText("c1=0.4\n");
        	param.appendText("c2=2\n");
        	param.appendText("w=0.2\n");
        	param.appendText("r1=0.6\n");
        	param.appendText("r2=0.6\n");
        	param.appendText("swarmsize=70");
        	
        	Particle p=app.algopso(plg);fitness=p.getFitness();
        for(int j=0;j<p.getPbest().size();j++)
        {solution.appendText(p.getPbest().get(j)+" ");} 
        int in=instance.getSelectionModel().getSelectedIndex();
        s.getData().add(new XYChart.Data(""+in,fitness));
        graphe.getData().addAll(s);
        }
              
        //System.out.print(app.m[i][j]);
		//if(algo.getSelectionModel().getSelectedItem()=="BFS") {}
	}
	
}
