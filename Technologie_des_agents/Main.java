

import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;

import jade.core.Profile;
import jade.core.ProfileImpl;
import jade.core.Runtime;
import jade.wrapper.AgentController;
import jade.wrapper.ContainerController;
import jade.wrapper.StaleProxyException;

import javax.swing.JTextField;
import javax.swing.JButton;
import javax.swing.JLabel;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.awt.event.ActionEvent;
import java.awt.TextArea;
import java.awt.Font;
import java.awt.Color;
import javax.swing.JComboBox;
import javax.swing.DefaultComboBoxModel;
import java.awt.TextField;

public class Main extends JFrame {

	private JPanel contentPane;
	private JTextField prixT;
	private JTextField prixReserveT;
	private JTextField prixMaxT;
	private JTextField miseT;
	static Runtime rt;
	static Profile p;
	static ContainerController mc;
	static int x=0;

	ArrayList<Acheteur>ListeAcheteurs = new ArrayList<Acheteur>();
	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Main frame = new Main();
					frame.setVisible(true);
					
			}catch (Exception e) {
				e.printStackTrace();
			
			}
			} 
		});
	}

	/**
	 * Create the frame.
	 */
	public Main() {
		setTitle("Application d'enchère");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 917, 493);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		contentPane.setLayout(new BorderLayout(0, 0));
		setContentPane(contentPane);
		
		JPanel panel = new JPanel();
		contentPane.add(panel, BorderLayout.CENTER);
		panel.setLayout(null);
		
		JPanel panel_1 = new JPanel();
		panel_1.setBackground(Color.LIGHT_GRAY);
		panel_1.setBounds(21, 26, 415, 189);
		panel.add(panel_1);
		panel_1.setLayout(null);
		
		prixT = new JTextField();
		prixT.setColumns(10);
		prixT.setBounds(188, 85, 162, 20);
		panel_1.add(prixT);
		
		prixReserveT = new JTextField();
		prixReserveT.setColumns(10);
		prixReserveT.setBounds(188, 120, 162, 20);
		panel_1.add(prixReserveT);
		
		JLabel lblNewLabel = new JLabel("Produit");
		lblNewLabel.setFont(new Font("Times New Roman", Font.BOLD, 12));
		lblNewLabel.setBounds(25, 48, 99, 14);
		panel_1.add(lblNewLabel);
		
		JLabel lblPrix = new JLabel("Prix");
		lblPrix.setFont(new Font("Times New Roman", Font.BOLD, 12));
		lblPrix.setBounds(25, 87, 83, 17);
		panel_1.add(lblPrix);
		
		JLabel lblPrixReserve = new JLabel("Prix reserve");
		lblPrixReserve.setFont(new Font("Times New Roman", Font.BOLD, 12));
		lblPrixReserve.setBounds(25, 126, 99, 14);
		panel_1.add(lblPrixReserve);
		
		JLabel lblNewLabel_1 = new JLabel("Partie vendeur");
		lblNewLabel_1.setForeground(Color.RED);
		lblNewLabel_1.setFont(new Font("Times New Roman", Font.BOLD, 16));
		lblNewLabel_1.setBounds(150, 11, 136, 14);
		panel_1.add(lblNewLabel_1);
		
		JComboBox ListProduit = new JComboBox();
		ListProduit.setModel(new DefaultComboBoxModel(new String[] {"Clavier", "Ecran", "Souris", "Disque dur","Unité centrale"}));
		ListProduit.setBounds(188, 45, 162, 20);
		panel_1.add(ListProduit);
		
		JLabel lblNewLabel_3 = new JLabel("Temps");
		lblNewLabel_3.setFont(new Font("Times New Roman", Font.BOLD, 12));
		lblNewLabel_3.setBounds(22, 164, 46, 14);
		panel_1.add(lblNewLabel_3);
		
		TextField timeT = new TextField();
		timeT.setBounds(188, 156, 162, 22);
		panel_1.add(timeT);
		
		JPanel panel_2 = new JPanel();
		panel_2.setBackground(Color.LIGHT_GRAY);
		panel_2.setBounds(480, 26, 390, 189);
		panel.add(panel_2);
		panel_2.setLayout(null);
		
		prixMaxT = new JTextField();
		prixMaxT.setColumns(10);
		prixMaxT.setBounds(175, 93, 151, 20);
		panel_2.add(prixMaxT);
		
		miseT = new JTextField();
		miseT.setColumns(10);
		miseT.setBounds(175, 124, 151, 20);
		panel_2.add(miseT);
		
		JButton btnAjouterAch = new JButton("Ajouter acheteur");
		btnAjouterAch.setFont(new Font("Times New Roman", Font.BOLD, 12));
		btnAjouterAch.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				double prixMax =Double.parseDouble(prixMaxT.getText());
				double mise =Double.parseDouble(miseT.getText());
			
				
				Acheteur acheteur=new Acheteur();
				acheteur.setPrixMax(prixMax);
				acheteur.setMise(mise);
				ListeAcheteurs.add(acheteur);
				//vider les textFileds
				prixMaxT.setText("");
				miseT.setText("");
				
			
			}
		});
		btnAjouterAch.setBounds(185, 155, 141, 23);
		panel_2.add(btnAjouterAch);
		
		JLabel lblPrixSeuil = new JLabel("Prix seuil");
		lblPrixSeuil.setFont(new Font("Times New Roman", Font.BOLD, 12));
		lblPrixSeuil.setBounds(31, 96, 68, 14);
		panel_2.add(lblPrixSeuil);
		
		JLabel lblMise = new JLabel("Mise");
		lblMise.setFont(new Font("Times New Roman", Font.BOLD, 12));
		lblMise.setBounds(31, 134, 68, 14);
		panel_2.add(lblMise);
		
		JLabel lblNewLabel_2 = new JLabel("Partie acheteur");
		lblNewLabel_2.setForeground(Color.RED);
		lblNewLabel_2.setFont(new Font("Times New Roman", Font.BOLD, 16));
		lblNewLabel_2.setBounds(137, 9, 123, 14);
		panel_2.add(lblNewLabel_2);
		
		
		JComboBox ListNbrAch = new JComboBox();
		ListNbrAch.setBounds(175, 50, 151, 20);
		panel_2.add(ListNbrAch);
		ListNbrAch.setModel(new DefaultComboBoxModel(new String[] {"1", "2", "3", "4", "5", "6", "7", "8"}));
		
		JLabel lblNombreAcheteurs = new JLabel("Nombre d'acheteurs");
		lblNombreAcheteurs.setBounds(31, 53, 124, 14);
		panel_2.add(lblNombreAcheteurs);
		lblNombreAcheteurs.setFont(new Font("Times New Roman", Font.BOLD, 12));
		
		JButton btnLancerEnch = new JButton("Lancer l'enchère!");
		btnLancerEnch.setFont(new Font("Times New Roman", Font.BOLD, 12));
		TextArea textArea = new TextArea();
		textArea.setBounds(21, 264, 849, 160);
		panel.add(textArea);
		
		btnLancerEnch.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				double prix =Double.parseDouble(prixT.getText());
				double prixReserve =Double.parseDouble(prixReserveT.getText());
			    int nbrAchT=Integer.parseInt(ListNbrAch.getSelectedItem().toString());
			    String Designation= ListProduit.getSelectedItem().toString();
			    long time=Long.parseLong(timeT.getText());
			   int j=1;
				try {
				
					 for(Acheteur A:ListeAcheteurs) {
							System.out.println("liste acheteurs .."+ListeAcheteurs.get(j-1).PrixMax);
							System.out.println("liste acheteurs .."+ListeAcheteurs.get(j-1).Mise);
							j++;
						}
					 Runtime rt=Runtime.instance();
				    Object[] arg1=new Object[3]; Object[] arg2=new Object[6];
				     rt.setCloseVM(true);
					Profile p=new ProfileImpl();
					p.setParameter(Profile.MAIN_HOST,"localhost");
					p.setParameter(Profile.GUI,"false");
					ContainerController mc=rt.createMainContainer(p);
					int nbrAch=nbrAchT;
					
			        for(int i=1; i<=nbrAch;i++) {
			        	
			        	arg1[0]=ListeAcheteurs.get(i-1).PrixMax; arg1[1]=ListeAcheteurs.get(i-1).Mise;  
			      
			        	
						AgentController ag1=mc.createNewAgent("Acheteur"+i, "Acheteur",new Object[] {ListeAcheteurs.get(i-1).PrixMax,ListeAcheteurs.get(i-1).Mise,textArea,Designation});
				        ag1.start();
			           }
			        
			         
			        arg2[0]=prixT.getText(); arg2[1]=prixReserveT.getText(); arg2[2]=nbrAch; arg2[3]=textArea; arg2[4]=Designation; arg2[5]=time;
			        AgentController ag2=mc.createNewAgent("Vendeur", "V1",arg2);
			        ag2.start();
			        
			        
						// TODO Auto-generated catch block
					} catch (StaleProxyException e2) {e2.printStackTrace();}
			    
			} 
		});
		btnLancerEnch.setBounds(329, 227, 171, 30);
		panel.add(btnLancerEnch);
		
		JLabel lblResultat = new JLabel("Resultat");
		lblResultat.setFont(new Font("Times New Roman", Font.BOLD, 12));
		lblResultat.setBounds(31, 235, 113, 14);
		panel.add(lblResultat);
		
		
	}
}
