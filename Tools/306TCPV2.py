import tkinter as tk
from tkinter import messagebox
import socket

# --- TCP Client Logic (No Changes) ---

class IOTClient:
    def __init__(self):
        self.sock = None

    def connect(self, ip, port):
        """Attempts to establish a TCP connection to the server."""
        try:
            self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.sock.settimeout(5)
            self.sock.connect((ip, port))
            self.sock.settimeout(None) 
            return True
        except socket.error as e:
            messagebox.showerror("Connection Error", f"Could not connect to {ip}:{port}\nError: {e}")
            self.sock = None
            return False

    def send_command(self, formatted_message):
        """Sends the fully formatted (^####CTTTT or custom) message."""
        if not self.sock:
            messagebox.showerror("Send Error", "Not connected to the IOT server.")
            return False

        try:
            # Append CRLF termination and encode for transmission.
            full_command = (formatted_message + '\r\n').encode('ascii')
            self.sock.sendall(full_command)
            return True
        except socket.error as e:
            messagebox.showerror("Send Error", f"Failed to send command: {e}")
            self.close()
            return False

    def close(self):
        """Closes the socket connection."""
        if self.sock:
            self.sock.close()
            self.sock = None
            print("Connection closed.")


# --- Tkinter GUI Logic ---

class ControlApp:
    def __init__(self, master):
        self.master = master
        master.title("ECE 306 IOT TCP Client")
        
        master.geometry("500x820") 
        
        self.client = IOTClient()
        self.is_connected = False

        # --- Connection Variables ---
        self.ip_var = tk.StringVar(value="") 
        self.port_var = tk.StringVar(value="")
        self.password_var = tk.StringVar(value="") 
        self.custom_cmd_var = tk.StringVar(value="") 

        # --- EXPLICIT COMMAND DURATION DEFINITIONS ---
        self.TURN_SHORT = 175
        self.TURN_MEDIUM = 350

        self.T_SHORT = 500
        self.T_MEDIUM = 1000
        self.T_LONG = 2000
        self.T_STOP = 0
        
        # Column mapping for readability
        # COLUMNS[time_in_ms] = grid_column_index
        self.COLUMNS = {self.T_SHORT: 1, self.T_MEDIUM: 2, self.T_LONG: 3, self.T_STOP: 1} 
        
        self.create_widgets()
        
    def create_widgets(self):
        # 1. Connection Frame
        conn_frame = tk.LabelFrame(self.master, text="TCP Connection & Security", padx=10, pady=10)
        conn_frame.pack(padx=10, pady=10, fill="x")

        tk.Label(conn_frame, text="IP Address:").grid(row=0, column=0, padx=5, pady=5, sticky="w")
        tk.Entry(conn_frame, textvariable=self.ip_var).grid(row=0, column=1, padx=5, pady=5, sticky="ew")

        tk.Label(conn_frame, text="Port:").grid(row=1, column=0, padx=5, pady=5, sticky="w")
        tk.Entry(conn_frame, textvariable=self.port_var).grid(row=1, column=1, padx=5, pady=5, sticky="ew")

        # Hidden Password Field
        tk.Label(conn_frame, text="Password (4-char):").grid(row=2, column=0, padx=5, pady=5, sticky="w")
        tk.Entry(conn_frame, textvariable=self.password_var, show="*").grid(row=2, column=1, padx=5, pady=5, sticky="ew")

        self.connect_button = tk.Button(conn_frame, text="CONNECT", bg="green", fg="white", command=self.handle_connect)
        self.connect_button.grid(row=3, column=0, columnspan=2, pady=10, sticky="ew")
        
        # Status text starts red for DISCONNECTED
        self.status_label = tk.Label(conn_frame, text="Status: DISCONNECTED", fg="red") 
        self.status_label.grid(row=4, column=0, columnspan=2, sticky="ew")
        
        conn_frame.grid_columnconfigure(1, weight=1)

        # ---
        
        # 2. Command Frame
        cmd_frame = tk.LabelFrame(self.master, text="Car Control Commands (^####CTTTT)", padx=10, pady=10)
        cmd_frame.pack(padx=10, pady=10, fill="x")
        
        # --- EXPLICIT COMMAND BUTTONS START HERE (NO LOOPS) ---
        
        # Header Row
        tk.Label(cmd_frame, text="Movement", font='Helvetica 10 bold').grid(row=0, column=0, padx=5, pady=5)
        tk.Label(cmd_frame, text=f"Short ({self.T_SHORT}ms)", font='Helvetica 10 bold').grid(row=0, column=1, padx=5, pady=5)
        tk.Label(cmd_frame, text=f"Medium ({self.T_MEDIUM}ms)", font='Helvetica 10 bold').grid(row=0, column=2, padx=5, pady=5)
        tk.Label(cmd_frame, text=f"Long ({self.T_LONG}ms)", font='Helvetica 10 bold').grid(row=0, column=3, padx=5, pady=5)
        
        row_counter = 1
        
        # FORWARD (F)
        tk.Label(cmd_frame, text="Forward").grid(row=row_counter, column=0, padx=5, pady=5, sticky="w")
        
        # F-SHORT   (500ms) 
        tk.Button(cmd_frame, text=f"F 500ms", command=lambda c='F', t=self.T_SHORT: self.handle_send(c, t)).grid(row=row_counter, column=self.COLUMNS[self.T_SHORT], padx=5, pady=5, sticky="ew")
        # F-MEDIUM  (1s) 
        tk.Button(cmd_frame, text=f"F 1s", command=lambda c='F', t=self.T_MEDIUM: self.handle_send(c, t)).grid(row=row_counter, column=self.COLUMNS[self.T_MEDIUM], padx=5, pady=5, sticky="ew")
        # F-LONG    (2s)
        tk.Button(cmd_frame, text=f"F 2s", command=lambda c='F', t=self.T_LONG: self.handle_send(c, t)).grid(row=row_counter, column=self.COLUMNS[self.T_LONG], padx=5, pady=5, sticky="ew")
        row_counter += 1
        
        # REVERSE (B) 
        tk.Label(cmd_frame, text="Reverse").grid(row=row_counter, column=0, padx=5, pady=5, sticky="w")
        
        # B-SHORT   (500ms) 
        tk.Button(cmd_frame, text=f"B 500ms", command=lambda c='B', t=self.T_SHORT: self.handle_send(c, t)).grid(row=row_counter, column=self.COLUMNS[self.T_SHORT], padx=5, pady=5, sticky="ew")
        # B-MEDIUM  (1s) 
        tk.Button(cmd_frame, text=f"B 1s", command=lambda c='B', t=self.T_MEDIUM: self.handle_send(c, t)).grid(row=row_counter, column=self.COLUMNS[self.T_MEDIUM], padx=5, pady=5, sticky="ew")
        # B-LONG    (2s) 
        tk.Button(cmd_frame, text=f"B 2s", command=lambda c='B', t=self.T_LONG: self.handle_send(c, t)).grid(row=row_counter, column=self.COLUMNS[self.T_LONG], padx=5, pady=5, sticky="ew")
        row_counter += 1
        
        # TURN RIGHT (R)
        tk.Label(cmd_frame, text="Turn Right").grid(row=row_counter, column=0, padx=5, pady=5, sticky="w")
        
        # R-SHORT   (175ms) 
        tk.Button(cmd_frame, text=f"Right 45", command=lambda c='R', t=self.TURN_SHORT: self.handle_send(c, t)).grid(row=row_counter, column=self.COLUMNS[self.T_SHORT], padx=5, pady=5, sticky="ew")
        # R-MEDIUM  (350ms) 
        tk.Button(cmd_frame, text=f"Right 90", command=lambda c='R', t=self.TURN_MEDIUM: self.handle_send(c, t)).grid(row=row_counter, column=self.COLUMNS[self.T_MEDIUM], padx=5, pady=5, sticky="ew")
        # R-LONG    (2s) 
        tk.Button(cmd_frame, text=f"R 2s", command=lambda c='R', t=self.T_LONG: self.handle_send(c, t)).grid(row=row_counter, column=self.COLUMNS[self.T_LONG], padx=5, pady=5, sticky="ew")
        row_counter += 1
        
        # TURN LEFT (L)
        tk.Label(cmd_frame, text="Turn Left").grid(row=row_counter, column=0, padx=5, pady=5, sticky="w")
        
        # L-SHORT   (175ms) 
        tk.Button(cmd_frame, text=f"Left 45", command=lambda c='L', t=self.TURN_SHORT: self.handle_send(c, t)).grid(row=row_counter, column=self.COLUMNS[self.T_SHORT], padx=5, pady=5, sticky="ew")
        # L-MEDIUM  (350ms) 
        tk.Button(cmd_frame, text=f"Left 90", command=lambda c='L', t=self.TURN_MEDIUM: self.handle_send(c, t)).grid(row=row_counter, column=self.COLUMNS[self.T_MEDIUM], padx=5, pady=5, sticky="ew")
        # L-LONG    (2s) 
        tk.Button(cmd_frame, text=f"L 2s", command=lambda c='L', t=self.T_LONG: self.handle_send(c, t)).grid(row=row_counter, column=self.COLUMNS[self.T_LONG], padx=5, pady=5, sticky="ew")
        row_counter += 1
        
        # STOP/BRAKE (S) 
        tk.Label(cmd_frame, text="Stop/Brake").grid(row=row_counter, column=0, padx=5, pady=5, sticky="w")
        
        # S-STOP (Placed in the first time column)
        tk.Button(cmd_frame, text=f"S{self.T_STOP:04d}", command=lambda c='S', t=self.T_STOP: self.handle_send(c, t)).grid(row=row_counter, column=self.COLUMNS[self.T_STOP], padx=5, pady=5, sticky="ew")
        row_counter += 1
        
        # --- EXPLICIT COMMAND BUTTONS END HERE ---

        cmd_frame.grid_columnconfigure(1, weight=1)
        cmd_frame.grid_columnconfigure(2, weight=1)
        cmd_frame.grid_columnconfigure(3, weight=1)
        
        # ---
        
        # 3. Display Pads Frame
        pad_frame = tk.LabelFrame(self.master, text="Display Pad Commands (T=9999)", padx=10, pady=10)
        pad_frame.pack(padx=10, pady=10, fill="x")
        
        for i in range(1, 9):
            row = (i - 1) // 4
            col = (i - 1) % 4
            tk.Button(
                pad_frame, 
                text=f"Pad {i}", 
                bg="#A9A9A9",
                command=lambda c=str(i), t=9999: self.handle_send(c, t)
            ).grid(row=row, column=col, padx=5, pady=5, sticky="ew")
            
        for i in range(4):
            pad_frame.grid_columnconfigure(i, weight=1)

        # ---
        
        # 4. LCD Commands Frame
        lcd_frame = tk.LabelFrame(self.master, text="LCD Commands", padx=10, pady=10)
        lcd_frame.pack(padx=10, pady=10, fill="x")
        
        tk.Button(
            lcd_frame,
            text="Toggle LCD (T)",
            bg="#FFB84D",
            command=lambda c='T', t=0: self.handle_send(c, t)
        ).grid(row=0, column=0, padx=5, pady=5, sticky="ew")

        tk.Button(
            lcd_frame,
            text="Temp LCD ON (O)",
            bg="#FFB84D",
            command=lambda c='O', t=9999: self.handle_send(c, t)
        ).grid(row=0, column=1, padx=5, pady=5, sticky="ew")
        
        lcd_frame.grid_columnconfigure(0, weight=1)
        lcd_frame.grid_columnconfigure(1, weight=1)

        # ---
        
        # 4. Custom Command Frame
        custom_frame = tk.LabelFrame(self.master, text="Custom Command (Appends \\r\\n)", padx=10, pady=10)
        custom_frame.pack(padx=10, pady=10, fill="x")

        tk.Label(custom_frame, text="Command String:").grid(row=0, column=0, padx=5, pady=5, sticky="w")
        tk.Entry(custom_frame, textvariable=self.custom_cmd_var).grid(row=0, column=1, padx=5, pady=5, sticky="ew")
        
        tk.Button(custom_frame, 
                  text="SEND CUSTOM COMMAND", 
                  bg="#929292", fg="white", 
                  command=self.handle_custom_send
        ).grid(row=1, column=0, columnspan=2, pady=5, sticky="ew")
        
        custom_frame.grid_columnconfigure(1, weight=1)


    def handle_connect(self):
        """Handles the Connect/Disconnect button press."""
        if self.is_connected:
            self.client.close()
            self.is_connected = False
            self.update_status("DISCONNECTED", "red", "CONNECT", "green")
        else:
            try:
                ip = self.ip_var.get()
                port = int(self.port_var.get())
            except ValueError:
                messagebox.showerror("Input Error", "Port must be a number.")
                return
            
            # Check for blank fields before connection
            if not ip or not port:
                messagebox.showerror("Input Error", "IP Address and Port cannot be blank.")
                return

            if self.client.connect(ip, port):
                self.is_connected = True
                self.update_status("CONNECTED", "black", "DISCONNECT", "red") # Status is black when connected
    
    def handle_send(self, command, time_ms):
        """
        Handles sending a command, formatting it as ^####CTTTT.
        C: Command (1 char), TTTT: Time in ms (4 digits).
        """
        if not self.is_connected:
            messagebox.showwarning("Warning", "Please connect to the IOT server first.")
            return

        password = self.password_var.get()
        if len(password) != 4 or not password.isdigit():
            messagebox.showerror("Security Error", "Password must be exactly 4 digits.")
            return
            
        # Format the time as a 4-digit string
        time_str = f"{time_ms:04d}"
        
        # Assemble the final 10-character protocol message: ^####CTTTT
        formatted_message = f"^{password}{command}{time_str}"

        if self.client.send_command(formatted_message):
            # Status text is black when reporting a successful send
            self.status_label.config(text=f"Status: Sent '{formatted_message}'", fg="black") 
        else:
            self.update_status("DISCONNECTED", "red", "CONNECT", "green")
            
    def handle_custom_send(self):
        """
        Handles sending the raw command from the custom input field.
        """
        if not self.is_connected:
            messagebox.showwarning("Warning", "Please connect to the IOT server first.")
            return
            
        custom_command = self.custom_cmd_var.get()
        if not custom_command:
             messagebox.showwarning("Input Error", "Custom command field cannot be empty.")
             return
             
        if self.client.send_command(custom_command):
            # Status text is black when reporting a successful send
            self.status_label.config(text=f"Status: Sent custom command: '{custom_command}'", fg="black")
        else:
            self.update_status("DISCONNECTED", "red", "CONNECT", "green")


    def update_status(self, status_text, status_fg, button_text, button_bg):
        """Updates the status label and connect button."""
        self.status_label.config(text=f"Status: {status_text}", fg=status_fg)
        self.connect_button.config(text=button_text, bg=button_bg)
        

if __name__ == '__main__':
    root = tk.Tk()
    app = ControlApp(root)
    # Ensure the socket is closed when the main window is closed
    root.protocol("WM_DELETE_WINDOW", lambda: [app.client.close(), root.destroy()])
    root.mainloop()