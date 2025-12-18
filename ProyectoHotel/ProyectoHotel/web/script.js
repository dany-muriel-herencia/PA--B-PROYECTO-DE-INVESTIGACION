// Variables Globales
let currentUser = null; // { nombre, role, token, dni }

document.addEventListener('DOMContentLoaded', () => {
    // Verificar si hay sesion guardada
    const savedUser = localStorage.getItem('hotelUser');
    if (savedUser) {
        currentUser = JSON.parse(savedUser);
        mostrarDashboard();
    }
});

// --- LOGIN LOGIC ---
function toggleLoginFields() {
    const tipo = document.getElementById('login-tipo').value;
    const lblUser = document.getElementById('lbl-user');
    const groupPass = document.getElementById('group-pass');
    const groupNote = document.getElementById('group-pass-note');

    if (tipo === "3") { // Cliente
        lblUser.innerHTML = '<i class="fa fa-id-card"></i> Identificación';
        groupPass.style.display = "block";
        groupNote.style.display = "block";
    } else {
        lblUser.innerHTML = (tipo === "1") ? '<i class="fa fa-user-shield"></i> Usuario Admin' : '<i class="fa fa-id-badge"></i> DNI Empleado';
        groupPass.style.display = "block";
        groupNote.style.display = "none";

        if (tipo === "1") {
            groupNote.style.display = "block";
            groupNote.innerHTML = '<i class="fa fa-info-circle"></i> Clave por defecto: admin';
        }
    }
}

async function handleLogin(e) {
    e.preventDefault();
    const tipo = document.getElementById('login-tipo').value;
    const user = document.getElementById('login-user').value;
    const pass = document.getElementById('login-pass').value;

    try {
        const res = await fetch(`/api/login?tipo=${tipo}&user=${user}&password=${pass}`, { method: 'POST' });
        const data = await res.json();

        if (data.success) {
            currentUser = {
                nombre: data.nombre,
                role: data.role,
                dni: user
            };
            localStorage.setItem('hotelUser', JSON.stringify(currentUser));
            mostrarDashboard();
        } else {
            alert("Error de acceso: " + data.mensaje);
        }
    } catch (err) {
        alert("Error crítico: Imposible conectar con el servidor central.");
        console.error(err);
    }
}

function logout() {
    currentUser = null;
    localStorage.removeItem('hotelUser');
    location.reload(); // Recargar para limpiar estado
}

// --- DASHBOARD NAVIGATION ---
function mostrarDashboard() {
    document.getElementById('login-view').classList.add('hidden');
    document.getElementById('dashboard-view').classList.remove('hidden');

    document.getElementById('user-display').textContent = `BIENVENIDO, ${currentUser.nombre.toUpperCase()}`;

    const adminNav = document.getElementById('admin-nav');
    const clientNav = document.getElementById('client-nav');

    // Ocultar todo primero
    adminNav.classList.add('hidden');
    clientNav.classList.add('hidden');

    if (currentUser.role === 'admin') {
        adminNav.classList.remove('hidden');
    } else if (currentUser.role === 'cliente') {
        clientNav.classList.remove('hidden');
    }

    // Cargar vista default
    showSection('habitaciones');
}

function showSection(sectionId) {
    // Ocultar todas las secciones
    document.querySelectorAll('.content-section').forEach(el => {
        el.classList.add('hidden');
        el.style.opacity = 0;
    });

    // Manejar estado activo en nav
    document.querySelectorAll('.nav-btn').forEach(btn => btn.classList.remove('active'));
    const activeBtn = Array.from(document.querySelectorAll('.nav-btn')).find(btn => btn.getAttribute('onclick').includes(sectionId));
    if (activeBtn) activeBtn.classList.add('active');

    // Mostrar la elegida con un ligero delay para animacion
    const target = document.getElementById(`section-${sectionId}`);
    target.classList.remove('hidden');
    setTimeout(() => {
        target.style.transition = 'opacity 0.4s ease';
        target.style.opacity = 1;
    }, 50);

    // Cargar datos según sección
    if (sectionId === 'habitaciones') cargarHabitaciones();
    if (sectionId === 'empleados') cargarEmpleados();
    if (sectionId === 'stock') cargarStock();
    if (sectionId === 'restaurant') cargarRestaurante();
}

// --- HABITACIONES ---
async function cargarHabitaciones() {
    const grid = document.getElementById('habitaciones-grid');
    grid.innerHTML = '<p class="loading"><i class="fa fa-spinner fa-spin"></i> Consultando disponibilidad...</p>';

    try {
        const res = await fetch('/api/habitaciones');
        const data = await res.json();

        grid.innerHTML = '';
        data.forEach(h => {
            const card = document.createElement('div');
            card.className = `card ${h.estado}`;
            let icon = 'fa-bed';
            if (h.tipo === 'Matrimonial') icon = 'fa-heart';
            if (h.tipo === 'Suite') icon = 'fa-crown';

            // Boton liberar para admin
            let actionBtn = '';
            if (currentUser.role === 'admin' && h.estado !== 'Disponible') {
                actionBtn = `<button class="btn-sm btn-logout" onclick="liberarHabitacion(${h.numero}, event)" title="Liberar Forzosa" style="position: absolute; top: 10px; right: 10px; border-radius: 50%; width: 35px; height: 35px; padding:0;"><i class="fa fa-broom"></i></button>`;
            }

            card.innerHTML = `
                <div class="card-header"><i class="fa ${icon}"></i> ${actionBtn}</div>
                <div class="card-body">
                    <div class="type">${h.tipo}</div>
                    <h3>Habitación ${h.numero}</h3>
                    <div class="price">S/ ${h.precio} <small style="font-size: 0.8rem; color: var(--text-muted); font-weight: 400;">/ noche</small></div>
                    <span class="status-badge ${h.estado}">${h.estado}</span>
                </div>
             `;

            if (h.estado === 'Disponible' && (currentUser.role === 'cliente' || currentUser.role === 'admin')) {
                card.onclick = () => abrirModalReserva(h);
                card.style.cursor = 'pointer';
            }
            grid.appendChild(card);
        });
    } catch (err) { console.error(err); }
}

async function liberarHabitacion(num, e) {
    e.stopPropagation(); // Evitar abrir modal reserva
    if (!confirm(`¿Desea restablecer el estado de la habitación ${num} a DISPONIBLE?`)) return;

    const res = await fetch(`/api/liberar_habitacion?num=${num}`, { method: 'POST' });
    const data = await res.json();
    alert(data.mensaje);
    cargarHabitaciones();
}

// --- EMPLEADOS ---
async function cargarEmpleados() {
    const tbody = document.querySelector('#tabla-empleados tbody');
    tbody.innerHTML = '<tr><td colspan="5" class="loading">Sincronizando registros...</td></tr>';

    const res = await fetch('/api/empleados');
    const data = await res.json();

    tbody.innerHTML = '';
    data.forEach(e => {
        const tr = document.createElement('tr');
        tr.innerHTML = `
            <td><strong>${e.nombre}</strong></td>
            <td><code>${e.dni}</code></td>
            <td><span class="status-badge" style="background: var(--primary); color: white;">${e.rol}</span></td>
            <td>S/ ${e.salario}</td>
            <td>
                <button class="btn-sm btn-logout" onclick="eliminarEmpleado('${e.dni}')" title="Dar de baja"><i class="fa fa-user-minus"></i></button>
            </td>
        `;
        tbody.appendChild(tr);
    });
}

async function eliminarEmpleado(dni) {
    if (!confirm("¿Está seguro de dar de baja a este colaborador?")) return;
    const res = await fetch(`/api/empleados/eliminar?dni=${dni}`, { method: 'POST' });
    cargarEmpleados();
}

// --- STOCK ---
async function cargarStock() {
    const tbody = document.querySelector('#tabla-stock tbody');
    tbody.innerHTML = '<tr><td colspan="4" class="loading">Consultando almacén...</td></tr>';

    const res = await fetch('/api/stock');
    const data = await res.json();

    tbody.innerHTML = '';
    data.forEach(s => {
        const tr = document.createElement('tr');
        tr.innerHTML = `
            <td>${s.nombre}</td>
            <td style="font-weight: 700;">${s.cantidad} und.</td>
            <td><span class="status-badge">${s.tipo}</span></td>
            <td>S/ ${s.precio}</td>
        `;
        tbody.appendChild(tr);
    });
}

function abrirModalStock() { document.getElementById('modal-stock').classList.remove('hidden'); }
function cerrarModalStock() { document.getElementById('modal-stock').classList.add('hidden'); }

async function procesarAgregarStock(e) {
    e.preventDefault();
    const nom = document.getElementById('stk-nombre').value;
    const cant = document.getElementById('stk-cantidad').value;
    const tipo = document.getElementById('stk-tipo').value;
    const precio = document.getElementById('stk-precio').value;

    await fetch(`/api/stock/agregar?nombre=${nom}&cantidad=${cant}&tipo=${tipo}&precio=${precio}`, { method: 'POST' });
    cerrarModalStock();
    cargarStock();
}

// --- RESTAURANTE ---
async function cargarRestaurante() {
    const grid = document.getElementById('restaurant-grid');
    grid.innerHTML = '<p class="loading">Preparando la carta...</p>';

    const res = await fetch('/api/stock');
    const data = await res.json(); // Reusamos endpoint de stock

    grid.innerHTML = '';
    const menu = data.filter(s => s.tipo === 'Comida' || s.tipo === 'Bebida');

    if (menu.length === 0) {
        grid.innerHTML = '<div style="grid-column: 1/-1; text-align: center; padding: 3rem;">Nuestros chefs están renovando el menú. Inténtelo más tarde.</div>';
        return;
    }

    menu.forEach(p => {
        const card = document.createElement('div');
        card.className = 'card';
        let icon = (p.tipo === 'Bebida') ? 'fa-glass-cheers' : 'fa-utensils';
        card.innerHTML = `
            <div class="card-header" style="height: 120px; font-size: 2.5rem; background: #f8fafc; color: var(--accent);"><i class="fa ${icon}"></i></div>
            <div class="card-body">
                <h3>${p.nombre}</h3>
                <div class="price">S/ ${p.precio}</div>
                <p style="color: var(--text-muted); font-size: 0.85rem; margin-bottom: 1rem;">Disponibilidad: ${p.cantidad}</p>
                <button class="btn-primary btn-block" onclick="pedirComida('${p.nombre}')"><i class="fa fa-shopping-cart"></i> Solicitar</button>
            </div>
        `;
        grid.appendChild(card);
    });
}

async function pedirComida(producto) {
    const cant = prompt(`¿Cuántas unidades de ${producto} desea solicitar a su suite?`, "1");
    if (!cant || isNaN(cant)) return;

    const res = await fetch(`/api/pedir_comida?dni=${currentUser.dni}&producto=${producto}&cantidad=${cant}`, { method: 'POST' });
    const data = await res.json();
    alert(data.mensaje);
    cargarRestaurante(); // Recargar stock visual
}

// --- RESERVA (Existente) ---
function abrirModalReserva(habitacion) {
    const modal = document.getElementById('modal-reserva');
    const today = new Date().toISOString().split('T')[0];
    document.getElementById('res-num').value = habitacion.numero;
    document.getElementById('res-num-display').value = `Habitación ${habitacion.numero} - ${habitacion.tipo}`;

    // No necesitamos poblar campos de texto ya que usaremos currentUser directamente en procesarReserva

    document.getElementById('res-entrada').value = today;
    modal.classList.remove('hidden');
}

function cerrarModal() {
    document.getElementById('modal-reserva').classList.add('hidden');
}

async function procesarReserva(e) {
    e.preventDefault();
    const num = document.getElementById('res-num').value;
    const dni = currentUser.dni;
    const nombre = currentUser.nombre;
    const entrada = document.getElementById('res-entrada').value;
    const salida = document.getElementById('res-salida').value;

    const res = await fetch(`/api/reservar?num=${num}&dni=${dni}&nombre=${encodeURIComponent(nombre)}&fechaEntrada=${entrada}&fechaSalida=${salida}`, { method: 'POST' });
    const data = await res.json();
    alert(data.mensaje);
    cerrarModal();
    cargarHabitaciones();
}
