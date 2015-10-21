/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Graficas;

import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JOptionPane;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

/**
 *
 * @author lab
 */
public class GraficaEncoders extends Grafica {
    final XYSeries A1 = new XYSeries("Aceleracion angular 1");
    final XYSeries A2 = new XYSeries("Aceleración angular 2");
    final XYSeries W1 = new XYSeries("Velocidad angular 1");
    final XYSeries W2 = new XYSeries("Velocidad angular 2");
    final XYSeriesCollection coleccionAceleracionAngular = new XYSeriesCollection();
    final XYSeriesCollection coleccionVelocidadAngular = new XYSeriesCollection();
    private JFreeChart chartAA;
    private JFreeChart chartWA;


    public GraficaEncoders(ArrayList<Double> a1, ArrayList<Double> a2, ArrayList<Double> w1,ArrayList<Double> w2) {
        super("Grafica: Encoders");
        
        A1.add(0,0);
        A2.add(0,0);
        W1.add(0,0);
        W2.add(0,0);
        
        this.agregarValoresASeries(a1,a2,w1,w2);
        
        coleccionAceleracionAngular.addSeries(A1);
        coleccionAceleracionAngular.addSeries(A2);
        
        coleccionVelocidadAngular.addSeries(W1);
        coleccionVelocidadAngular.addSeries(W2);
        
        chartAA = ChartFactory.createXYLineChart("Aceleracion angular (rad/s²) en cada ciclo", "# de ciclo", "α (rad/s²)", coleccionAceleracionAngular, PlotOrientation.VERTICAL, true, true, false);
        chartWA = ChartFactory.createXYLineChart("Velocidad angular (rad/s) por ciclo", "# de ciclo", "ω (rad/s)", coleccionVelocidadAngular, PlotOrientation.VERTICAL, true, true, false);
        
        ChartPanel panelAA = new ChartPanel(chartAA);
        ChartPanel panelWA = new ChartPanel(chartWA);
        
        ventanaGrafica.add(panelWA);
        ventanaGrafica.add(panelAA);
        
        ventanaGrafica.pack();
    }

    
    public void agregarValoresASeries(ArrayList<Double> a1, ArrayList<Double> a2, ArrayList<Double> w1,ArrayList<Double> w2){
        A1.clear();
        A2.clear();
        W1.clear();
        W2.clear();
        
        int inicio = 0;
        
        /*if(a1.size() > 80){
            inicio = a1.size() - 80;
        }*/
        
        for (int ciclo = 0; ciclo < a1.size(); ciclo++) {
            agregarASeries(a1.get(ciclo), a2.get(ciclo), w1.get(ciclo), w1.get(ciclo));
        }
        
        contadorCiclo = a1.size();
    }
    
    public void agregarASeries(double a1, double a2, double w1, double w2){
        if(contadorCiclo > 0 && contadorCiclo % nMuestrasEnPantalla == 0){
            try {
                this.guardarGraficaComoPNG((JFreeChart)chartAA.clone(), "Encoders/AA/Aceleracion-angular"+contadorCiclo/nMuestrasEnPantalla);
                this.guardarGraficaComoPNG((JFreeChart)chartWA.clone(), "Encoders/WA/Velocidad-angular"+contadorCiclo/nMuestrasEnPantalla);
            } catch (CloneNotSupportedException ex) {
                JOptionPane.showMessageDialog(null, "Error al copiar charts");
            }
        }
        
        if(contadorCiclo > nMuestrasEnPantalla){
            A1.remove(0);
            A2.remove(0);
            W1.remove(0);
            W2.remove(0);
        }
        
        A1.add(contadorCiclo,a1);
        A2.add(contadorCiclo,a2);
        W1.add(contadorCiclo,w1);
        W2.add(contadorCiclo,w2);
        contadorCiclo++;
    }
}
