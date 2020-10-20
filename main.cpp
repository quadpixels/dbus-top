// 2020-10-18

#include <stdio.h>
#include <systemd/sd-bus.h>
#include <chrono>

std::chrono::time_point<std::chrono::steady_clock> g_t0;
long ElapsedMillis() {
	std::chrono::time_point<std::chrono::steady_clock> t = std::chrono::steady_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(t - g_t0).count();
}

// Run this tool with SUDO

bool IS_USER_BUS = false;
sd_bus* g_bus = nullptr;

int AcquireBus(sd_bus** ret) {

	int r;
	r = sd_bus_new(&g_bus);
	if (r < 0) { printf("Could not allocate bus: %s\n", strerror(-r)); return 0; }

	r = sd_bus_set_monitor(g_bus, true);
	if (r < 0) { printf("Could not set monitor mode: %s\n", strerror(-r)); return 0; }

	r = sd_bus_negotiate_creds(g_bus, true, _SD_BUS_CREDS_ALL);
	if (r < 0) { printf("Could not enable credentials: %s\n", strerror(-r)); return 0; }

	r = sd_bus_negotiate_timestamp(g_bus, true);
	if (r < 0) { printf("Could not enable timestamps: %s\n", strerror(-r)); return 0; }

	r = sd_bus_negotiate_fds(g_bus, true);
	if (r < 0) { printf("Could not enable fds: %s\n", strerror(-r)); return 0; }

	r = sd_bus_set_bus_client(g_bus, true);
	if (r < 0) { printf("Could not enable bus client: %s\n", strerror(-r)); return 0; }
	
	if (IS_USER_BUS) {
		r = sd_bus_set_address(g_bus, "haha");
		if (r < 0) { printf("Could not set user bus: %s\n", strerror(-r)); return 0; }
	} else {
		r = sd_bus_set_address(g_bus, "unix:path=/run/dbus/system_bus_socket");
		if (r < 0) { printf("Could not set system bus: %s\n", strerror(-r)); return 0; }
	}

	r = sd_bus_start(g_bus);
	if (r < 0) { printf("Could not connect to bus: %s\n", strerror(-r)); return 0; }

	return r;
}

int main() {
	g_t0 = std::chrono::steady_clock::now();

	uint32_t flags = 0;
	int r;
	AcquireBus(&g_bus);
	sd_bus_message* message;
	sd_bus_error error = SD_BUS_ERROR_NULL;
	r = sd_bus_message_new_method_call(g_bus, &message,
			"org.freedesktop.DBus",
			"/org/freedesktop/DBus",
			"org.freedesktop.DBus.Monitoring",
			"BecomeMonitor");
	if (r < 0) { printf("Could not create the BecomeMonitor function call\n"); return 0; }

	// Match conditions
	{
		r = sd_bus_message_open_container(message, 'a', "s");
		if (r < 0) { printf("Could not open container\n"); return 0; }

		r = sd_bus_message_close_container(message);
		if (r < 0) { printf("Could not close container\n"); return 0; }
	}

	r = sd_bus_message_append_basic(message, 'u', &flags);
	if (r < 0) { printf("Could not append flags\n"); return 0; }

	r = sd_bus_call(g_bus, message, 0, &error, nullptr);
	if (r < 0) { printf("Could not call org.freedesktop.DBus.Monitoring.BecomeMonitor %d, %s\n", r, strerror(-r)); return 0; }

	const char* unique_name;
	r = sd_bus_get_unique_name(g_bus, &unique_name);
	if (r < 0) { printf("Could not get unique name: %s\n", strerror(-r)); return 0; }
	printf("Unique name: %s\n", unique_name);

	printf("Monitoring bus stream\n");
	while (true) {
		struct sd_bus_message* m = nullptr;
		r = sd_bus_process(g_bus, &m);
		printf("%ld ms: ", ElapsedMillis());

		const char* path = sd_bus_message_get_path(m);
		if (path) printf("Path: %s ", path);

		const char* iface = sd_bus_message_get_interface(m);
		if (iface) printf("Interface: %s ", iface);

		const char* destination = sd_bus_message_get_destination(m);
		if (destination) printf("Dest: %s ", destination);

		printf("\n");
		r = sd_bus_wait(g_bus, (uint64_t)(-1));
		if (r < 0) { printf("Failed to wait on bus: %s\n", strerror(-r)); }
	}

	return 0;
}
