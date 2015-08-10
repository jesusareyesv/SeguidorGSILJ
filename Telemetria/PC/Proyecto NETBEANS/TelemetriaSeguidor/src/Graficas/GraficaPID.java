/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Graficas;

import java.util.ArrayList;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
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
    
    private JFreeChart chartPID;

    public GraficaPID(ArrayList<Double> p, ArrayList<Double> i, ArrayList<Double> d) {
        super("Grafica: PID");
        derivativo.add(0,0);
        proporcional.add(0,0);
        integral.add(0,0);
        
        agregarValores(p, i, d);
        
        coleccion.addSeries(proporcional);
        coleccion.addSeries(integral);
        coleccion.addSeries(derivativo);
        
        chartPID = ChartFactory.createXYLineChart("PID desde el Arduino", "Ciclo", "Valor", coleccion, PlotOrientation.VERTICAL, true, true, false);
        
        ChartPanel panel = new ChartPanel(chartPID);
        
        ventanaGrafica.add(panel);
        
        ventanaGrafica.pack();
        
    }
    
    public void agregarValores(ArrayList<Double> p, ArrayList<Double> i, ArrayList<Double> d){
        derivativo.clear();
        integral.clear();
        proporcional.clear();
        
        int inicio = 0;
        
        if(p.size() > 200){
            inicio = p.size() - 80;
        }
        
        for (int ciclo = inicio; ciclo < p.size(); ciclo++) {
            derivativo.add(ciclo+1, d.get(ciclo));
            proporcional.add(ciclo+1, p.get(ciclo));
            integral.add(ciclo+1, i.get(ciclo));
        }
        
        contadorCiclo = p.size();
    }
    
    public void agregar(double p, double i, double d){
        if(contadorCiclo > 200){
            proporcional.remove(0);
            derivativo.remove(0);
            integral.remove(0);
        }
        
        proporcional.add(contadorCiclo, p);
        derivativo.add(contadorCiclo, d);
        integral.add(contadorCiclo, i);
        
        contadorCiclo++;
    }
    
    
}
