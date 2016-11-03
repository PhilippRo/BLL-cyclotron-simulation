/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package bllgui;
import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import javax.swing.*;

import java.util.ArrayList;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
/**
 *
 * @author philipp
 */
public class BllGui extends JFrame{
    /**
     * @param args the command line arguments
     */
    SpinnerNumberModel nZyks;
    JPanel ConfPanel;
    ArrayList <ZykConfPanel> zyks;
    JTextField timeScale;
    JLabel timeScaleLabel;
    JPanel TopBox;
    
    public BllGui(){
        super();
        setTitle("Zyklotron Simulation Konfigurator");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        getContentPane().setLayout(new java.awt.BorderLayout());
        setSize(500,300);
        
        ConfPanel = new JPanel();
        ConfPanel.setLayout(new java.awt.GridLayout(2,2));
        getContentPane().add(ConfPanel, BorderLayout.CENTER);
       
        TopBox = new JPanel();
        javax.swing.BoxLayout topLay = new javax.swing.BoxLayout(TopBox, javax.swing.BoxLayout.X_AXIS);
        TopBox.setLayout(topLay);
        nZyks = new SpinnerNumberModel();
        nZyks.setMinimum(1);
        nZyks.setMaximum(4);
        nZyks.setValue(1);
        timeScaleLabel = new JLabel("Zeitmaßstab 1:");
        timeScale = new JTextField();
        
        TopBox.add(new JSpinner(nZyks));
        TopBox.add(javax.swing.Box.createHorizontalStrut(200));
        TopBox.add(timeScaleLabel);
        TopBox.add(timeScale);
        getContentPane().add(TopBox, BorderLayout.NORTH);
                
        JButton button = new JButton("Simulation Starten");
        getContentPane().add(button, BorderLayout.SOUTH);
        
        zyks = new ArrayList<>();
        ZykConfPanel z = new ZykConfPanel();
        zyks.add(z);
        ConfPanel.add(z);
                    
        nZyks.addChangeListener(new ChangeListener(){
            @Override
            public void stateChanged(ChangeEvent e) {
                int newZyks = (int) nZyks.getNumber();
                if(newZyks > zyks.size()){
                    ZykConfPanel z = new ZykConfPanel();
                    zyks.add(z);
                    ConfPanel.add(z);
                }else if(newZyks < zyks.size()){
                    int toRem = zyks.size() - 1;
                    zyks.remove(toRem);
                    ConfPanel.remove(toRem);
                }
                
                ConfPanel.updateUI();
            }
        });
        
        button.addActionListener(new ActionListener(){
            @Override
            public void actionPerformed(ActionEvent e) {
                String strs = "";
                for(int i = 0; i < zyks.size(); i++){
                    strs = strs + " " + zyks.get(i).getCallable();
                }
                try {
                   Process myProcess = Runtime.getRuntime().exec("./main " + strs
                        +" -timeScale " + timeScale.getText());
                   myProcess.waitFor();
                } catch (IOException | InterruptedException ex) {
                    Logger.getLogger(BllGui.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        
        });
        
    }
    
    public static void main(String[] args) {
        // TODO code application logic here
        BllGui f = new BllGui();
        f.setVisible(true);
    }
    
}
