#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct vozidlo {
	char znacka[20];
	char model[20];
	char spz[10];
	float spotreba;
	struct vozidlo* dalsi;
}tVozidlo;

tVozidlo* nactiSeznam(char* jmSoub, char* jmPobocky) {
	FILE* f = fopen(jmSoub, "r");
	if (f == NULL) {
		printf("CHYBA CTENI\n");
		return 1;
	}
	tVozidlo* voz = malloc(sizeof(tVozidlo));
	tVozidlo* pos = voz;
	if (voz == NULL) {
		printf("CHYBA ALLOKOVANI\n");
		return 1;
	}
	char buffer[100];
	while (fgets(buffer, 100, f)) {
		if (buffer[0] == 'P') {
			char* del = strchr(buffer, ';');
			char* comp = del + 1;
			comp[strlen(comp) - 1] = '\0';
			if (!strcmp(jmPobocky, comp)) {
				int j = 0;
				tVozidlo* pred = voz;
				while (fscanf(f,"%[^;];%[^;];%[^;];%f", pos->znacka, pos->model, pos->spz, &pos->spotreba) == 4) {
					if (j > 0) {
						pos->dalsi = malloc(sizeof(tVozidlo));
						pred = pos;
						pos = pos->dalsi;
					}
					j++;
				}
				pred->dalsi = NULL;
				free(pred->dalsi);
				break;
			}

		}
	}
	fclose(f);
	return voz;
}
void vypisPobocky(char* jmSoub) {
	FILE* f = fopen(jmSoub, "r");
	if (f == NULL) {
		printf("CHYBA CTENI\n");
		return 1;
	}
	char buffer[100];
	while (fgets(buffer, 100, f)) {
		if (buffer[0] == 'P') {
			char* del = strchr(buffer, ';');
			char* comp = del + 1;
			printf("%s\n", comp);
		}
	}
	fclose(f);
}
void ulozNadPrumer(tVozidlo* seznamAut) {
	tVozidlo* v = seznamAut;
	int n = 0, prum = 0;
	
	while (v != NULL) {
		n++;
		prum += v->spotreba;
		v = v->dalsi;
	}
	if (n == 0) {
		printf("CHYBA");
		return 1;
	}
	float i = prum / n;
	FILE* f = fopen("nadprum.txt", "w");
	if (f == NULL) {
		printf("CHYBA OTEVERENI");
		return 1;
	}
	while (seznamAut != NULL) {
		if (seznamAut->spotreba > i) fprintf(f, "%s;%s;%s;%f\n", seznamAut->znacka, seznamAut->model, seznamAut->spz, seznamAut->spotreba);
		seznamAut = seznamAut->dalsi;
	}
}

int main(void) {
	vypisPobocky("data.csv");
	tVozidlo* t = nactiSeznam("data.csv", "pobocka 1");
	ulozNadPrumer(t);
	
	
}