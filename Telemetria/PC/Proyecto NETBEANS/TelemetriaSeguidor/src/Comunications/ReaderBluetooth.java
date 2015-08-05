/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Comunications;

import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Random;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JOptionPane;

/**
 *
 * @author jesus.reyes
 */
public class ReaderBluetooth extends Thread {
    private InputStream input =null;
    private boolean online = false;
    
    protected String entrada;
   
    public ReaderBluetooth(InputStream in){
        this.input = in;
        this.entrada = "";
        online = true;
        this.start();
    }

    @Override
    public void run() {
        int counter = 0;
        while(online){
            String s = this.read();
            if(s != "" && !s.equals(entrada)){
                entrada = s;
            }
            System.out.println(counter+"///"+s);
            counter++;
        }
        
        this.disconect();
    }
    
    private String read(){
        
        String incoming="";
        
        try{    
            byte singleData = 0;
            
                do{
            
                singleData = (byte) input.read();
                incoming += new String(new byte[]{singleData});
                
                }while(singleData != 0);
                /*if(singleData != 0){
                //if(singleData != BotCommunicator.NEW_LINE_ASCII){
                    incoming += new String(new byte[]{singleData});
                }else{
                    incoming = "***NL***";
                }*/

        } catch (IOException ex) {
            System.err.println("Problema al leer desde el flujo de entrada.");
        }
        //JOptionPane.showMessageDialog(null, this, incoming, MIN_PRIORITY);
        return incoming;
    }
    
    protected void parar(){
        this.online = false;
    }
    
    private void disconect(){
        if(!online){
            try {
                input.close();
            } catch (IOException ex) {
                System.err.println("Problema al cerrar el flujo de entrada.");
            }
        }
    }
    
    private String read2(){
        String s = "";
        
        Random r = new Random();
        
        int p,i,d,sPID,pwmi,pwmd,ts;
        
        p = r.nextInt();i = r.nextInt();d = r.nextInt(); sPID = p+i+d;
        pwmi = r.nextInt();pwmd = r.nextInt();ts = r.nextInt();
        
        s = p + "/" + i + "/" + d+ "/" +sPID+ "/" +pwmi+ "/" +pwmd+ "/" +ts;
        
        return s;
        
    }

    public String getEntrada() {
        return entrada;
    }
    
    
}
