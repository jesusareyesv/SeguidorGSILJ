/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
//
package Comunications;

import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;
import java.awt.*;
import java.awt.Color;
//import gnu.io.SerialPortEventListener;
//import gnu.io.*;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.OutputStream;
import java.io.InputStream;
import gnu.io.*;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.TooManyListenersException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.sound.midi.SysexMessage;
import javax.swing.JOptionPane;

/**
 *
 * @author jesus
 */
public class BotCommunicator implements IOBluetoothConstants{//implements SerialPortEventListener {
    
    private Enumeration ports = null;//para los puertos encontrados
    private HashMap portMap =new HashMap();//el mapa de identificadores de puertos
    private CommPortIdentifier selectedPortIdentifier =null;//identificador puerto actual
    private SerialPort serialPort = null;//numero de puerto actual
    private boolean isConectado = false;//bandera de conexion
    
    private InputStream input = null;
    private OutputStream output = null;
    
    private ReaderBluetooth reader;
    private SenderBluetooth sender;
   
    
    String mensajes="";//salida a GUI
    String incoming;
    String puertoSeleccionado;

    private String ultimoMensaje;
    
    public BotCommunicator(){
        mensajes="";
        ultimoMensaje="";
        puertoSeleccionado = "";
    }
    /*
    @Override
    public void serialEvent(SerialPortEvent spe) {
        if(spe.getEventType() == SerialPortEvent.DATA_AVAILABLE){
            try{
                byte singleData=(byte) input.read();
                
                if(singleData != NEW_LINE_ASCII){
                    incoming=new String(new byte[]{singleData});
                    agregarMensaje("Nueva data disponible: \n" + incoming);
                }else{
                    System.out.println();
                }
            }catch(Exception e){
                this.agregarMensaje("Falla al leer la data desde el dispositivo en el puerto " + serialPort.getName());
            }
        }
    }*/
    
    public boolean searchPorts(){
        ports = CommPortIdentifier.getPortIdentifiers();
        
        String salidaPane = "Puertos disponibles para conexión serial";
        ArrayList<String> puertos=new ArrayList();
        
        while(ports.hasMoreElements()){
            //this.Hola();
            CommPortIdentifier currentPort= (CommPortIdentifier)ports.nextElement();
            
            if(currentPort.getPortType() == CommPortIdentifier.PORT_SERIAL){
                puertos.add(currentPort.getName());
                portMap.put(currentPort.getName(), currentPort);
            }
        }
        
        if(portMap.size() > 0){
            puertoSeleccionado=(String) JOptionPane.showInputDialog(null, "Seleccione el puerto a usar:", salidaPane, JOptionPane.QUESTION_MESSAGE, null, puertos.toArray(), null);
            return true;
        }else{
            JOptionPane.showMessageDialog(null, "No existen puertos disponibles para la comunicacion serial. Verifique las conexiones.", "Error al conectar", JOptionPane.ERROR_MESSAGE);
            return false;
        }
    }
    
    public boolean connect() throws IOException{
        boolean confirm = false;
        
        selectedPortIdentifier=(CommPortIdentifier)portMap.get(puertoSeleccionado);
        
        CommPort commPort=null;
        
        try{
            commPort=selectedPortIdentifier.open("TigerControlPanel", TIMEOUT);
            serialPort=(SerialPort)commPort;
            
            this.setIsConectado(true);
            
            agregarMensaje(puertoSeleccionado + " fue abierto satisfactoriamente.");
            confirm = true;
            //serialPort.setBaudBase(baudRate);         OOOOOOOOOOOOOOOOOOJJJJJJJJOOOOOOOOOOOOOOOOOO
        }
        catch(PortInUseException e){
            agregarMensaje(puertoSeleccionado + " se encuentra en uso. ("+e.toString()+")");
            
        }
        catch(Exception e){
            agregarMensaje("\nFalló al abrir "+puertoSeleccionado);
        }
        
        return confirm;
    }
    
    public boolean initIOStream()
    {
        //return value for whether opening the streams is successful or not
        boolean successful = false;

        try {
            //
            input = serialPort.getInputStream();
            
            reader = new ReaderBluetooth(input);
            
            output = serialPort.getOutputStream();
            
            sender = new SenderBluetooth(output);
            sender.writeData(0+"");
            successful = true; 
        }
        catch (IOException e) {
            agregarMensaje("\nI/O Streams failed to open. (" + e.toString() + ")");
        }
        
        return successful;
    }
    
    public boolean initListener(){
        try{
            serialPort.addEventListener((SerialPortEventListener) this);
            serialPort.notifyOnDataAvailable(true);
            return true;
        }
        catch(TooManyListenersException e){
            agregarMensaje("\nHay muchos listeners inicializados. "+e.getMessage());
            
        }
        return false;
    }
    
    public void disconnect(){
        if(isConectado){
            try{
                //writeData(0, 0);
                serialPort.removeEventListener();
                serialPort.close();
                input.close();
                output.close();
                setIsConectado(false);
                agregarMensaje("Desconectado.");

            }catch(Exception e){
                agregarMensaje("No se puedo desconectar del pueto especificado." + serialPort.getName()+  " excepcion: " + e.toString());
            }
        }else{
            JOptionPane.showMessageDialog(null, "No se puede desconectar porque no se encuentra conectado.", "Error al desconectar", JOptionPane.ERROR_MESSAGE);
        }
    }
    
    

    public boolean isIsConectado() {
        return isConectado;
    }

    public void setIsConectado(boolean isConectado) {
        this.isConectado = isConectado;
    }
/*
    public void writeData(int leftThrottle, int rightThrottle) {
        try{
            output.write(leftThrottle);
            output.flush();
            
            output.write(DASH_ASCII);
            output.flush();
            
            output.write(SPACE_ASCII);
            output.flush();
            
            
            
        }catch(Exception e){
            agregarMensaje("Falla al escribir la data en el puerto "+serialPort.getName()+".");
        }
    }
    
    //@Override
    public void run(){  
        do{
            this.searchPorts();

            try {
                this.connect();
            } catch (IOException ex) {
                Logger.getLogger(BotCommunicator.class.getName()).log(Level.SEVERE, null, ex);
            }

            if(isIsConectado())
                if(initIOStream())
                    if(initListener())
                        JOptionPane.showMessageDialog(null, "Conectado satisfactoriamente a "+puertoSeleccionado);
        }while(!isConectado);
        
        /*while(activo){
            
        }    
    }*/
    
    public boolean iniciar(){
        boolean cancell = false;
            
            if(this.puertoSeleccionado != null && searchPorts()){
                try {
                    cancell = !connect();
                } catch (IOException ex) {
                    agregarMensaje("Error al conectar con el puerto seleccionado");
                }

                if(isIsConectado())
                    if(initIOStream()){
                        JOptionPane.showMessageDialog(null, "Conectado satisfactoriamente a "+puertoSeleccionado);
                        return true;
                    }
            }else{
                JOptionPane.showMessageDialog(null, "No ha seleccionado nigún puerto para la comunicación o no existen puertos disponibles.", "Error al abrir el puerto serial.", JOptionPane.ERROR_MESSAGE);
            }
            
            return false;
    }
    
    public boolean parar(){
        
        if(isConectado){
            this.reader.parar();

            if(this.sender.disconnect()){

                serialPort.removeEventListener();
                serialPort.close();
                setIsConectado(false);
                agregarMensaje("Desconectado.");
                return true;
            }
        }
        
        return false;
        
        
    }
    
    public void agregarMensaje(String s){
        mensajes+=s+"\n";
        ultimoMensaje=s;
        JOptionPane.showMessageDialog(null, ultimoMensaje);
    }

    public ReaderBluetooth getReader() {
        return reader;
    }

    public SenderBluetooth getSender() {
        return sender;
    }

    public String getPuertoSeleccionado() {
        return puertoSeleccionado;
    }

    
    
    
}
