/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package bllgui;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
/**
 *
 * @author philipp
 */
public class ZykConfPanel extends JPanel{
    private class Confs{
        public Confs(String paraName, String paraCall){
            name = paraName;
            callable = paraCall;
        }
        public String name; 
        public String callable;
    }
    
    JLabel[] header;
    JLabel[] e;
    JTextField[] vals;
    JTextField[] pows;
    JRadioButton rel, conf;
    ArrayList<Confs> zyks;
    JList selectList;
    
    public ZykConfPanel(){
        super();
        this.setMinimumSize(new java.awt.Dimension(600, 400));
        
        zyks = new ArrayList<>();
        zyks.add(new Confs("Elektron Relativistisch", "-rel ElektronRelativistisch 1,602e-19 1e-3 5e-2 1e2 9,109e-31 5e-5 1,137e-7 "));
        
        zyks.add(new Confs("Elektron Klassisch", "-cla ElektronKlassisch 1,602e-19 1e-3 5e-2 1e2 9,109e-31 5e-5 1,137e-7 "));
        
        zyks.add(new Confs("Wasserstoff Relativistisch", "-rel WasserstoffRelativistisch 1,602e-19 1e3 5e-2 1e2 3,817e-26 1e9 2,38292833e-2 "));
        
        zyks.add(new Confs("Wasserstoff Klassisch", "-cla WasserstoffKlassisch 1,602e-19 1e3 5e-2 1e2 3,817e-26 1e9 2,38292833e-2 "));
        
        zyks.add(new Confs("Natrium Relativistisch", "-rel NatriumRelativistisch 1,602e-19 1e3 5e-2 1e2 3,817e-26 1e9 2,38292833e-2 ")); 
        
        zyks.add(new Confs("Natrium Klassisch", "-cla NatriumKlassisch 1,602e-19 1e3 5e-2 1e2 3,817e-26 1e9 2,38292833e-2 ")); 
        
        zyks.add(new Confs("Gold Relativistisch", "-rel GoldRelativistisch 3,204e-19 1e3 5e-2 1e2 3,817e-26 1e9 8,808660669e-2 "));
        
        zyks.add(new Confs("Gold Klassisch", "-cla GoldKlassisch 3,204e-19 1e3 5e-2 1e2 3,817e-26 1e9 8,808660669e-2 "));
        
        
        header = new JLabel[8];
        header[0] = new JLabel("Name");
        header[1] = new JLabel("Ladung [q]");
        header[2] = new JLabel("Spannung [V]");
        header[3] = new JLabel("Dicke [m]");
        header[4] = new JLabel("Startgeschwindigkeit [m/s]");
        header[5] = new JLabel("Masse [kg]");
        header[6] = new JLabel("Magnetfeld [t]");
        header[7] = new JLabel("Frequenz [1/s]");
        
        e = new JLabel[8];
        vals = new JTextField[8];
        pows = new JTextField[8];
        rel = new JRadioButton("relativistisch");
        conf = new JRadioButton("Vorkonfiguriert");
        for(int i = 0; i < 8 ; i++){
            e[i] = new JLabel("e");
            vals[i] = new JTextField();
            pows[i] = new JTextField();
        }
        vals[7] = new JTextField();
        
        String[] name = new String[zyks.size()];
        for(int i = 0; i < zyks.size(); i++){
            name[i] = zyks.get(i).name;
        }
        selectList = new JList(name);
        
         conf.addChangeListener(new ChangeListener(){
            @Override
            public void stateChanged(ChangeEvent e) {
                if(conf.isSelected()){
                    setUpChangeView();
                }else{
                    setUpConf();
                }
            }
        });
        
         conf.setSelected(true);
         
        setUpChangeView();
        
    }
    
    private void setUpConf(){
        removeAll();
        setLayout(new GridLayout(11,4));
        setBorder(BorderFactory.createEtchedBorder(Color.black, Color.lightGray));     
        
        this.add(conf);
        this.add(new JLabel(""));
        this.add(new JLabel(""));
        this.add(new JLabel(""));
        this.add(new JLabel(""));
        this.add(new JLabel(""));
        this.add(new JLabel(""));
        this.add(new JLabel(""));
        this.add(header[0]);
        this.add(vals[0]);
        this.add(new JLabel(""));
        this.add(new JLabel(""));
        for(int i = 1; i < 8 ; i++){
            this.add(header[i]);
            this.add(vals[i]);
            this.add(e[i]);
            this.add(pows[i]);
        }
        
        this.add(rel);
        
        updateUI();
    }

    private void setUpChangeView(){
        this.removeAll();
        setLayout(new java.awt.BorderLayout());
        
        JScrollPane sp = new JScrollPane();
        sp.setViewportView(selectList);
        add(sp, BorderLayout.CENTER);
        add(conf, BorderLayout.NORTH);
        updateUI();
        
    }
    public String getCallable(){
       String ret;
       if(! conf.isSelected()){        
            ret = (rel.isSelected() ? "-rel " : "-cla ")
                   + '"' + vals[0].getText() + '"';

           for(int i = 1 ; i < 8 ; i++){
               ret = ret + " " + vals[i].getText() + "e" + pows[i].getText();
           }
       }else{
            ret = zyks.get(selectList.getSelectedIndex()).callable;
       }
       return ret;
    }
    
    
}
