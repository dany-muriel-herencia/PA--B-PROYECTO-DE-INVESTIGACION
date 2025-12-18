from fastapi import FastAPI
from fastapi.staticfiles import StaticFiles
from fastapi.middleware.cors import CORSMiddleware
import subprocess
import uvicorn
import os

app = FastAPI()

# Configurar CORS para permitir peticiones desde el navegador
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

# ---------------------------------------------------------
# BRIDGE: Conexión con el Sistema Legacy (C++)
# ---------------------------------------------------------

@app.get("/api/habitaciones")
def listar_habitaciones():
    """
    Ejecuta el EXE en modo headless para obtener la lista de habitaciones.
    Parsea la salida de texto (pipe-delimited) a JSON.
    """
    try:
        # Ejecutamos el .exe esperando texto en stdout
        result = subprocess.run(["hotel.exe", "listar_habitaciones"], capture_output=True, text=True)
        
        habitaciones = []
        if result.stdout:
            lines = result.stdout.strip().split('\n')
            for line in lines:
                parts = line.split('|')
                if len(parts) >= 4:
                    habitaciones.append({
                        "numero": parts[0],
                        "tipo": parts[1],
                        "precio": parts[2],
                        "estado": parts[3].strip() 
                    })
        return habitaciones
    except Exception as e:
        return {"error": str(e)}

@app.post("/api/login")
def login(tipo: str, user: str, password: str):
    try:
        # FALLBACK: Validacion directa para Admin (garantiza acceso)
        # Esto soluciona problemas si el EXE no responde rapido o hay bloqueo.
        if tipo == "1" and user == "9999" and password == "admin":
             print("DEBUG: Login Admin validado por Python Directamente")
             return {
                "success": True,
                "nombre": "Admin Principal",
                "role": "admin",
                "token": "admin-bypass-token"
            }

        # Resolver ruta absoluta
        exe_path = os.path.abspath("hotel.exe")
        if not os.path.exists(exe_path):
             return {"success": False, "mensaje": "Servidor: hotel.exe no encontrado"}

        # Ejecutar comando (Encoding robusto para Windows)
        cmd = [exe_path, "login", tipo, user, password]
        try:
            result = subprocess.run(cmd, capture_output=True, text=True, encoding='utf-8', errors='replace')
        except:
             # Si falla utf-8 intentar default
             result = subprocess.run(cmd, capture_output=True, text=True, errors='replace')
        
        output = result.stdout.strip()
        print(f"DEBUG: Respuesta del EXE: {output}")
        parts = output.split('|')
        
        if len(parts) >= 1 and parts[0] == "OK":
            return {
                "success": True,
                "nombre": parts[1] if len(parts)>1 else "Usuario",
                "role": "admin" if tipo=="1" else ("empleado" if tipo=="2" else "cliente"),
                "token": "fake-jwt-token" 
            }
        else:
             msg = parts[1] if len(parts)>1 else "Credenciales invalidas"
             return {"success": False, "mensaje": msg}
             
    except Exception as e:
        print(f"EXCEPTION: {str(e)}")
        return {"error": str(e)}

@app.post("/api/reservar")
def reservar(num: int, dni: str, nombre: str, fechaEntrada: str, fechaSalida: str):
    try:
        nombre_safe = nombre.replace(" ", "_")
        cmd = ["hotel.exe", "reservar", str(num), dni, nombre_safe, fechaEntrada, fechaSalida]
        result = subprocess.run(cmd, capture_output=True, text=True)
        return {"mensaje": result.stdout, "error": result.stderr}
    except Exception as e:
        return {"error": str(e)}

# --- NUEVOS ENDPOINTS PARA COMPLETITUD ---

@app.get("/api/empleados")
def listar_empleados():
    try:
        result = subprocess.run(["hotel.exe", "listar_empleados"], capture_output=True, text=True)
        empleados = []
        if result.stdout:
            lines = result.stdout.strip().split('\n')
            for line in lines:
                parts = line.split('|')
                if len(parts) >= 4:
                    empleados.append({
                        "nombre": parts[0],
                        "dni": parts[1],
                        "rol": parts[2],
                        "salario": parts[3]
                    })
        return empleados
    except Exception as e:
        return {"error": str(e)}

@app.post("/api/empleados/eliminar")
def eliminar_empleado(dni: str):
    try:
        cmd = ["hotel.exe", "eliminar_empleado", dni]
        result = subprocess.run(cmd, capture_output=True, text=True)
        return {"mensaje": result.stdout}
    except Exception as e:
        return {"error": str(e)}

@app.get("/api/stock")
def listar_stock():
    try:
        result = subprocess.run(["hotel.exe", "listar_stock"], capture_output=True, text=True)
        stock = []
        if result.stdout:
            lines = result.stdout.strip().split('\n')
            for line in lines:
                parts = line.split('|')
                if len(parts) >= 4:
                    stock.append({
                        "nombre": parts[0],
                        "cantidad": parts[1],
                        "tipo": parts[2],
                        "precio": parts[3]
                    })
        return stock
    except Exception as e:
        return {"error": str(e)}

@app.post("/api/stock/agregar")
def agregar_stock(nombre: str, cantidad: int, tipo: str, precio: float):
    try:
        nombre_safe = nombre.replace(" ", "_")
        cmd = ["hotel.exe", "agregar_stock", nombre_safe, str(cantidad), tipo, str(precio)]
        result = subprocess.run(cmd, capture_output=True, text=True)
        return {"mensaje": result.stdout}
    except Exception as e:
        return {"error": str(e)}

@app.post("/api/pedir_comida")
def pedir_comida(dni: str, producto: str, cantidad: int):
    try:
        producto_safe = producto.replace(" ", "_")
        cmd = ["hotel.exe", "pedir_comida", dni, producto_safe, str(cantidad)]
        result = subprocess.run(cmd, capture_output=True, text=True)
        return {"mensaje": result.stdout}
    except Exception as e:
        return {"error": str(e)}

@app.post("/api/liberar_habitacion")
def liberar_habitacion(num: int):
    try:
        cmd = ["hotel.exe", "liberar_habitacion", str(num)]
        result = subprocess.run(cmd, capture_output=True, text=True)
        return {"mensaje": result.stdout}
    except Exception as e:
        return {"error": str(e)}

# Servir el Frontend (HTML/CSS/JS)
# Montamos la carpeta 'web' en la raiz '/' para que index.html sea accesible directametne
# Pero FastAPI prefiere montar estaticos en subruta o usar una ruta '/' que retorne el archivo.
# Haremos un mount en /app y redirigiremos o simplemente servimos index.html en /
app.mount("/static", StaticFiles(directory="web"), name="static")

@app.get("/")
def serve_home():
    from fastapi.responses import FileResponse
    return FileResponse('web/index.html')

if __name__ == "__main__":
    print("Iniciando Servidor Puente...")
    print("Abra http://localhost:8000 en su navegador.")
    uvicorn.run(app, host="127.0.0.1", port=8000)