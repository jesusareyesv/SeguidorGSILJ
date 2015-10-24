/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Graficas;

import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.ChartUtilities;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

/**
 *
 * @author jesus
 */
public class GraficaPID extends Grafica{
    
    final XYSeries derivativo = new XYSeries("Derivativo");
    final XYSeries integral = new XYSeries("Integral");
    final XYSeries proporcional = new XYSeries("Proporcional");
    final XYSeries suma = new XYSeries("Suma");
    
    final XYSeriesCollection coleccion = new XYSeriesCollection();
    final XYSeriesCollection coleccionSuma = new XYSeriesCollection();
    
    private JFreeChart chartPID, chartSuma;

    public GraficaPID(ArrayList<Double> p, ArrayList<Double> i, ArrayList<Double> d, ArrayList<Double> s) {
        super("Grafica: PID");
        derivativo.add(0,0);
        proporcional.add(0,0);
        integral.add(0,0);
        suma.add(0, 0.0);
        
        //agregarValores(p, i, d, s);
        
        coleccion.addSeries(proporcional);
        coleccion.addSeries(integral);
        coleccion.addSeries(derivativo);
        
        coleccionSuma.addSeries(suma);
        
        chartPID = ChartFactory.createXYLineChart("PID desde el Arduino", "Ciclo", "Valor", coleccion, PlotOrientation.VERTICAL, true, true, false);
        chartSuma = ChartFactory.createXYLineChart("Suma PID", "Ciclo", "Valor", coleccionSuma, PlotOrientation.VERTICAL, true, true, false);
        
        agregarValores(p, i, d, s);
        
        ChartPanel panel = new ChartPanel(chartPID);
        ChartPanel panelSuma = new ChartPanel(chartSuma);
        
        ventanaGrafica.add(panel);
        ventanaGrafica.add(panelSuma);
        
        ventanaGrafica.pack();
        
    }
    
    public void agregarValores(ArrayList<Double> p, ArrayList<Double> i, ArrayList<Double> d, ArrayList<Double> s){
        derivativo.clear();
        integral.clear();
        proporcional.clear();
        suma.clear();
        
        int inicio = 0;
        
        /*if(p.size() > 10000){
            inicio = p.size() - 80;
        }*/
        
        for (int ciclo = inicio; ciclo < p.size(); ciclo++) {
            agregar(p.get(ciclo),i.get(ciclo),d.get(ciclo),s.get(ciclo));
        }
        
        contadorCiclo = p.size();
    }
    
    public void agregar(double p, double i, double d, double s){
        if(contadorCiclo > 0 && contadorCiclo % nMuestrasEnPantalla == 0){
            try {
                this.guardarGraficaComoPNG((JFreeChart)chartPID.clone(), "PID/PID/PID-grafica"+contadorCiclo/nMuestrasEnPantalla);
                this.guardarGraficaComoPNG((JFreeChart)chartSuma.clone(), "PID/Suma/Suma-grafica"+contadorCiclo/nMuestrasEnPantalla);
                
            } catch (CloneNotSupportedException ex) {
                JOptionPane.showMessageDialog(null, "Error al copiar charts");
            }
        }
        
        if(contadorCiclo > nMuestrasEnPantalla){
            proporcional.remove(0);
            derivativo.remove(0);
            integral.remove(0);
            suma.remove(0);
        }
        
        proporcional.add(contadorCiclo, p);
        derivativo.add(contadorCiclo, d);
        integral.add(contadorCiclo, i);
        suma.add(contadorCiclo, s);
        
        contadorCiclo++;
    }
    
    
}
