/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:11:02 by rexposit          #+#    #+#             */
/*   Updated: 2024/11/04 17:48:09 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "get_next_line.h"

void run_test(const char *filename) {
	int fd = open(filename, O_RDONLY);
	if (fd == -1) {
		perror("Error al abrir el archivo");
		return;
	}

	printf("=== Leyendo archivo: %s ===\n", filename);
	char *line;
	int line_number = 1;

	while ((line = get_next_line(fd)) != NULL) {
		printf("Línea %d: %s\n", line_number++, line);
		free(line);
	}
	close(fd);
	printf("=== Fin de lectura de: %s ===\n\n", filename);
}

int main() {
	const char *test_files[] = {
		"archivo_vacio.txt",
		"una_sola_linea.txt",
		"una_linea_con_salto.txt",
		"varias_lineas.txt",
		"linea_larga.txt",
		"diferentes_longitudes.txt",
		"sin_saltos.txt",
		"lineas_vacias.txt",
		"caracteres_especiales.txt",
		"archivo_inexistente.txt"
	};

	int num_tests = sizeof(test_files) / sizeof(test_files[0]);
	for (int i = 0; i < num_tests; i++) {
		printf("Iniciando prueba para archivo: %s\n", test_files[i]);
		run_test(test_files[i]);
	}
	return 0;
}