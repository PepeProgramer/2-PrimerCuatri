/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package proyectocirculos;

/**
 *
 * @author jordi
 */
public class ProyectoCirculos {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Circulo circulo = new Circulo(2,-1,1);
        Circulo circulo2 = new Circulo(5,3,4);
        //circulo2 = null;
        //circulo.pintar();
        float radio = circulo.getRadio();
        int nc = Circulo.cuantosCirculoshay();
        circulo = circulo2;
        circulo.setRadio(7);
        Circulo c3 = new Circulo(5,0,0);
        Punto p1 = c3.evaluar(0);
        Punto p2 = c3.evaluar(90);
        
        Circulo cc1 = new Circulo(5,-1,2);
        Circulo cc2 = new Circulo(3,-1,2);
        cc1.addConcentrico(cc2);
        
        float gr = cc2.grosor();
        
        Cuadro cuadro = new Cuadro(("Antonio wapo"));
        cuadro.addCirculo(3, 0, 0);
        cuadro.addCirculo(2, -5, 2);
        cuadro.addCirculo(2, -5, -2);
        
       double area = cuadro.area();
       
       Comprador comprador1 = new Comprador("rico");
       Comprador comprador2 = new Comprador("Pobre");
       
       Puja puja1 = new Puja(1000,comprador1, cuadro);
       Puja puja2 = new Puja(20,comprador2, cuadro);
       
       Comprador ganador = cuadro.ganadorSubasta();
       
    }
    
}
