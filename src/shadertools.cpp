#include "shadertools.hpp"

char*
readShaderSource(const char* shaderFile)
{
    FILE* fp = fopen(shaderFile, "r");
    long size;
    char* buf;

    if ( fp == NULL ) { return NULL; }

    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);

    fseek(fp, 0L, SEEK_SET);
    buf = (char*)malloc((size +1));
    fread(buf, 1, size, fp);

    buf[size] = '\0';
    fclose(fp);

    return buf;
}

GLuint
initProgram(const char* vShaderFile, const char* fShaderFile)
{
    GLuint program;
    int i;
    GLint  linked;
    
    Shader shaders[2] = {
	{ vShaderFile, GL_VERTEX_SHADER, NULL },
	{ fShaderFile, GL_FRAGMENT_SHADER, NULL }
    };

    program = glCreateProgram();
    for (i = 0; i < 2; ++i ) {
        GLuint shader;
        GLint  compiled;
        Shader* s;

	s = &shaders[i];
	s->source = readShaderSource( s->filename );
        if ( s->source == NULL ) {
	    fprintf(stderr, "Failed to read %s\n", s->filename);
	    exit( EXIT_FAILURE );
	}
	shader = glCreateShader( s->type );
        glShaderSource( shader, 1, (const GLchar**) &s->source, NULL );
	glCompileShader( shader );
	
	glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
	if ( !compiled ) {
            GLint  logSize;
            char* logMsg;

	    fprintf(stderr, "Failed to compile %s\n", s->filename);
	    glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logSize );
	    logMsg = (char*)malloc(logSize*sizeof(char));
	    glGetShaderInfoLog( shader, logSize, NULL, logMsg );
            fprintf(stderr, "%s\n", logMsg);
	    free(logMsg);

	    exit( EXIT_FAILURE );
	}
	free(s->source);
	glAttachShader( program, shader );
    }

    /* link  and error check */
    glLinkProgram(program);

    glGetProgramiv( program, GL_LINK_STATUS, &linked );
    if ( !linked ) {
        char* logMsg;
        GLint  logSize;

	fprintf(stderr, "Shader program failed to link\n");
	
	glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logSize);
	logMsg = (char*)malloc(logSize*sizeof(char));
	glGetProgramInfoLog( program, logSize, NULL, logMsg );
	fprintf(stderr, "%s\n", logMsg);
	free(logMsg);

	exit( EXIT_FAILURE );
    }

    return program;
}
