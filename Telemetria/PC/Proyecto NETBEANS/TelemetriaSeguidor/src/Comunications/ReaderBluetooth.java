/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Comunications;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
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
    private BufferedReader buffer;
    protected boolean available;
    protected String entrada;
   
    public ReaderBluetooth(InputStream in){
        this.input = in;
        this.entrada = "";
        online = true;
        buffer = new BufferedReader(new InputStreamReader(in));
        available = false;
        this.start();
    }

    @Override
    public void run() {
        while(online){
            String s = this.read();
            if(s != ""){
                entrada = s;
                available = true;
            }
        }
        
        this.disconect();
    }
    
    private String read(){
        
        String incoming="";
        
        try{   
            
            if(buffer.ready()){
                String temp = buffer.readLine();
                
                if(temp != null){
                    incoming = temp;
                    //available = true;
                }
            }
           /* byte singleData = 0;
            
                do{
            
                singleData = (byte) input.read();
                incoming += new String(new byte[]{singleData});
                
                }while(singleData != 0);
                /*if(singleData != 0){
                //if(singleData != BotCommunicator.NEW_LINE_ASCII){
                    incoming += new String(new byte[]{singleData});
                }else{
                    incoming = "***NL***";
                }
            */
        } catch (IOException ex) {
            JOptionPane.showMessageDialog(null, "Problema al leer desde el flujo de entrada.", "Lectura errónea", JOptionPane.WARNING_MESSAGE);
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
        available = false;
        return entrada;
    }

    public boolean isAvailable() {
        return available;
    }
    
}
