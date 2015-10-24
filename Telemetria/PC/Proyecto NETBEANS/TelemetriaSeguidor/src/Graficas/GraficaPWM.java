/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Graficas;

import static Graficas.Grafica.nMuestrasEnPantalla;
import java.awt.GridLayout;
import java.util.ArrayList;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
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
public class GraficaPWM extends Grafica{
    final XYSeries pwmi = new XYSeries("PWM motor izquierdo");
    final XYSeries pwmd = new XYSeries("PWM motor derecho");
    final XYSeries dutyCicle = new XYSeries("Tiempo de ciclo");
    final XYSeriesCollection coleccionPWM = new XYSeriesCollection();
    final XYSeriesCollection coleccionDutyCycle = new XYSeriesCollection();
    private JFreeChart chartPWM;
    private JFreeChart chartDutyCycle;


    public GraficaPWM(ArrayList<Integer> listaIzquierdo, ArrayList<Integer> listaDerecho, ArrayList<Integer> tciclo) {
        super("Grafica: PWM");
        
        pwmi.add(0,0);
        pwmd.add(0,0);
        dutyCicle.add(0,0);
        
        this.agregarValoresASeries(listaIzquierdo, listaDerecho,tciclo);
        
        coleccionPWM.addSeries(pwmi);
        coleccionPWM.addSeries(pwmd);
        coleccionDutyCycle.addSeries(dutyCicle);
        
        chartPWM = ChartFactory.createXYLineChart("PWM en cada ciclo de lectura", "Ciclo", "PWM", coleccionPWM, PlotOrientation.VERTICAL, true, true, false);
        chartDutyCycle = ChartFactory.createXYLineChart("Tiempo de ciclo", "# de ciclo", "Tiempo", coleccionDutyCycle, PlotOrientation.VERTICAL, true, true, false);
        
        ChartPanel panelPWM = new ChartPanel(chartPWM);
        ChartPanel panelTCiclo = new ChartPanel(chartDutyCycle);
        
        ventanaGrafica.add(panelPWM);
        ventanaGrafica.add(panelTCiclo);
        
        ventanaGrafica.pack();
    }

    
    public void agregarValoresASeries(ArrayList<Integer> apwmi,ArrayList<Integer> apwmd, ArrayList<Integer> tciclo){
        pwmi.clear();
        pwmd.clear();
        dutyCicle.clear();
        
        int inicio = 0;
        
        /*if(apwmi.size() > 80){
            inicio = apwmi.size() - 80;
        }*/
        
        for (int ciclo = inicio; ciclo < apwmi.size() - 1; ciclo++) {
            pwmi.add(ciclo+1,apwmi.get(ciclo));
            pwmd.add(ciclo+1,apwmd.get(ciclo));
            dutyCicle.add(ciclo+1,tciclo.get(ciclo));
        }
        
        contadorCiclo = apwmd.size();
    }
    
    public void agregarASeries(int i, int d, int tc){
        if(contadorCiclo > 0 && contadorCiclo % nMuestrasEnPantalla == 0){
            try {
                this.guardarGraficaComoPNG((JFreeChart)chartPWM.clone(), "PWM/PWM_motores/PWM-grafica"+contadorCiclo/nMuestrasEnPantalla);
                this.guardarGraficaComoPNG((JFreeChart)chartDutyCycle.clone(), "PWM/TiempoCiclo/TC-grafica"+contadorCiclo/nMuestrasEnPantalla);
            } catch (CloneNotSupportedException ex) {
                JOptionPane.showMessageDialog(null, "Error al copiar charts");
            }
        }
        
        if(contadorCiclo > nMuestrasEnPantalla){
            pwmi.remove(0);
            pwmd.remove(0);
            dutyCicle.remove(0);
        }
        
        pwmi.add(contadorCiclo,i);
        pwmd.add(contadorCiclo,d);
        dutyCicle.add(contadorCiclo,tc);
        contadorCiclo++;
    }
    
}
