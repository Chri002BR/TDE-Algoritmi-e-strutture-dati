typedef struct servizi_t *SERVIZI;

SERVIZI SERVIZIinit(int N);
void SERVIZIfree(SERVIZI s);

// Registra che la città 'citta' è servita dalla sede 'sede'
void SERVIZIassign(SERVIZI s, int citta, int sede);

// Calcola quante città sono servite dalla sede 'sedeIndex'
int SERVIZIcount(SERVIZI s, int sedeIndex);

// Imposta/Leggi la media
void SERVIZIsetMedia(SERVIZI s, float media);
float SERVIZIgetMedia(SERVIZI s);