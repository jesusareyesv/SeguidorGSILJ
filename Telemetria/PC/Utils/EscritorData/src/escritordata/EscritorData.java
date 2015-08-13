/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package escritordata;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.Timer;

/**
 *
 * @author jesus
 */
public class EscritorData {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws IOException {
        Timer timer = new Timer(100, new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    escribir();
                } catch (IOException ex) {
                    Logger.getLogger(EscritorData.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        });
        
        timer.start();
            
        while(true){
            
        }
    }
    
    public static void escribir() throws IOException{
        BufferedWriter writter = null;
        
        try {
            writter = new BufferedWriter(new FileWriter("/dev/ttyUSB02"));
        } catch (IOException ex) {
            Logger.getLogger(EscritorData.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        Random rnd = new Random();
        
        for (int i = 0; i < 30; i++) {
            double pr,in,de,suma;
            int pwml,pwmr,ct;
            
            pr = rnd.nextDouble();
            in = rnd.nextDouble();
            de = rnd.nextDouble();
            
            suma = pr+in+de;
            
            pwml = rnd.nextInt(255);
            pwmr = rnd.nextInt(255);
            ct = rnd.nextInt(1000);
            
            String toWrite = pr+"/"+in+"/"+de+"/"+suma+"/"+pwml+"/"+pwmr+"/"+ct;
            writter.write(toWrite);
            writter.newLine();
        }
        
        writter.close();
    }
    
    
}
