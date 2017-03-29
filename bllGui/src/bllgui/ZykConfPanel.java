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
        // q u d v0 m0 b f rmax
        zyks.add(new Confs("Elektron Relativistisch", "-rel ElektronRelativistisch 1.602e-19 5e2 1,0e-1 1e2 9,109e-31 7,14526e-4 2,0e7 1,0e0"));
        
        zyks.add(new Confs("Elektron Klassisch", "-cla ElektronKlassisch 1.602e-19 5e2 1,0e-1 1e2 9,109e-31 7,14526e-4 2,0e7 1,0e0"));
        
        zyks.add(new Confs("Proton Relativistisch", "-rel ProtonRelativistisch 1,602e-19 1e6 1,0e-1 1e2 1,673e-27 1,3123e0 2,0e7 1,0e0"));
        
        zyks.add(new Confs("Proton Klassisch", "-cla ProtonKlassisch 1,602e-19 1e6 1,0e-1 1e2 1,673e-27 1,3123e0 2,0e7 1,0e0"));
        
        zyks.add(new Confs("Alpha-Strahlung Relativistisch", "-rel Alpha-StrahlungRelativistisch 2,3205e-19 1e6 1,0e-1 1,0e2 6,645e-27 2,61e0 2,0e7 1,0e0"));
        
        zyks.add(new Confs("Alpha-Strahlung Klassisch", "-cla Alpha-StrahlungKlassisch 2,3205e-19 1e6 1,0e-1 1,0e2 6,645e-27 2,61e0 2,0e7 1,0e0")); 
        
        zyks.add(new Confs("Blei-208 Relativistisch", "-rel Blei-208Relativistisch 6,408e-19 1e6 1,0e-1 1e2 3,454e-25 6,7733e1 2,0e7 1,0e0"));
        
        zyks.add(new Confs("Blei-208 Klassisch", "-cla Blei-208Klassisch 6,408e-19 1e3 1,0e-1 1e2 3,454e-25 6,7733e1 2,0e7 1,0e0"));
        
        
        header = new JLabel[9];
        header[0] = new JLabel("Name");
        header[1] = new JLabel("Ladung [q]");
        header[2] = new JLabel("Spannung [V]");
        header[3] = new JLabel("Dicke [m]");
        header[4] = new JLabel("Startgeschwindigkeit [m/s]");
        header[5] = new JLabel("Masse [kg]");
        header[6] = new JLabel("Magnetfeld [t]");
        header[7] = new JLabel("Frequenz [1/s]");
        header[8] = new JLabel("Radius [m]");
        
        e = new JLabel[9];
        vals = new JTextField[9];
        pows = new JTextField[9];
        rel = new JRadioButton("relativistisch");
        conf = new JRadioButton("Vorkonfiguriert");
        for(int i = 0; i < 9 ; i++){
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
        setLayout(new GridLayout(12,4));
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
        for(int i = 1; i < 9 ; i++){
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

           for(int i = 1 ; i < 9 ; i++){
               ret = ret + " " + vals[i].getText() + "e" + pows[i].getText();
           }
       }else{
            ret = zyks.get(selectList.getSelectedIndex()).callable;
       }
       return ret;
    }
    
    
}
