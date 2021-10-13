package ejerciciosjava;

/**
 *
 * @author antonio
 */
public class EjerciciosJava {

    public static void main(String[] args) {
        Director director  = new Director("pepe", 356754655);
        Hotel h = new Hotel("Hotel de Pepe", "Vigo", 4);
        Hotel h2 = new Hotel("Paco's", "Malaga", 2);
        
        h.setDirector(director);
        
        /*System.out.println("Director: " + h.getDirector().getNombre());
        Cliente cli = new Cliente("356774411B", "Juan");
        cli.addReserva(new Reserva("10/09/2022", "12/09/2022", cli, h2));
        h2.addReserva(cli, "10/09/2022", "12/09/2022");
        System.out.println("-----------HOTEL-----------");
        for(Reserva r: h2.getReservas()) {
            System.out.println("Cliente: " + r.getCliente().getNombre() + " fecha entrada: " + r.getFechaEntrada());
        }
        System.out.println("-----------CLIENTE-----------");
        for(Reserva r : cli.getReservas()){
            System.out.println("Fecha de entrada: " + r.getFechaEntrada());
        }*/
        
        h2.setDirector(director);
        System.out.println("-------HOTELES-------");
        for(Hotel hotel : director.getHoteles()){
            System.out.println("Nombre: " + hotel.getNombre());
        }
       
    }
        
    
}
