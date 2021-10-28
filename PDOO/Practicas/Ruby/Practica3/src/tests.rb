require_relative 'vista_laberinto'
require_relative 'modelo_laberinto/laberinto'
require_relative 'Controlador_laberinto/controlador'

modelo = Modelo_laberinto::Laberinto.new
controlador = Controlador_laberinto::Controlador.new(modelo)
vista = Vista_laberinto.new(controlador)

vista.menu_usuario
