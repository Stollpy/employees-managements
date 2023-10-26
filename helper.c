char* uuid() {
    uuid_t id;
    uuid_generate(id);

    char *uuid_str = malloc(37);
    uuid_unparse_lower(id, uuid_str);

    return uuid_str;
}

char** explode(const char delimiter, const char* str) {
    int delimiterCount = 0;
    int i;
    char c;
    char* p = strdup(str);
    char* sub = (char*)malloc(strlen(str) + 1);
    sub[0] = '\0';
    char** r = (char**)malloc(sizeof(char*));

    for(i = 0; i < strlen(p); i++) {
        c = p[i];
        if (c == delimiter) {
            r = (char**)realloc(r, (delimiterCount + 1) * sizeof(char*));
            r[delimiterCount] = strdup(sub);
            sub[0] = '\0';
            delimiterCount++;
        } else {
            sub = strncat(sub, &c, 1);
        }
    }

    // add the last substring
    r = (char**)realloc(r, (delimiterCount + 1) * sizeof(char*));
    r[delimiterCount] = strdup(sub);
    sub[0] = '\0';
    delimiterCount++;

    delimiterCount++;
    r = (char**)realloc(r, (delimiterCount + 1) * sizeof(char*));
    r[delimiterCount] = NULL;

    free(p);
    free(sub);

    return r;
}
