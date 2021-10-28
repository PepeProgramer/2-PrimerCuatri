require_relative 'Estado_juego'
module Controlador_laberinto
  class Controlador

    attr_reader :estado_juego, :habitacion_usuario, :vidas, :modelo

    def initialize(laberinto)
      @vidas = 0
      @estado_juego = Estado_juego::EN_ENTRADA_LABERINTO
      @habitacion_usuario = nil
      @modelo = laberinto
    end

    def entrar(vidas)
      @vidas = vidas
      @habitacion_usuario = @modelo.puerta_entrada.habitacion_al_otro_lado(@habitacion_usuario)
      @estado_juego = Estado_juego::DENTRO_VIVO
      pared = Modelo_laberinto::Elemento_separador.nueva_pared(@habitacion_usuario, nil)
      @habitacion_usuario.set_lado(Modelo_laberinto::Direccion::SUR, pared)
    end

    def intentar_avanzar
      direction = Random.rand(4)
      #lado = @habitacion_usuario.get_lado(direction)
      if @habitacion_usuario.pasar(direction)
        @habitacion_usuario = @habitacion_usuario.get_lado(direction).habitacion_al_otro_lado(@habitacion_usuario)
      else
        @vidas -= 1
      end

      if @habitacion_usuario == nil
        @estado_juego = Estado_juego::EN_SALIDA_LABERINTO
        return -1
      end

      if @vidas <= 0
        @estado_juego = Estado_juego::DENTRO_MUERTO
        return -1
      else
        @estado_juego = Estado_juego::DENTRO_VIVO
        return direction
      end
    end
  end
end