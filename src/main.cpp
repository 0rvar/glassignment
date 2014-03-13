#include "main.hpp"

#define PI 3.141592f
#define BUFFER_SIZE 3000
#define BUFFER_OFFSET(i) ((char *)NULL + (i))
#define glsl(x) "#version 140\n" #x

#define CAMERA_SPEED 0.03
#define MOUSE_SENSITIVITY 0.005

/* OpenGL indices */
GLuint    locPosition;
GLuint    locNormal;
GLuint    idMVPMatrix;
GLuint    idMVMatrix;
GLuint    idNormalMatrix;

GLuint    idLightPosition;
GLuint    idLightIntensity;
GLuint    idAmbientIntensity;
GLuint    idMaterialAmbient;
GLuint    idMaterialDiffuse;
GLuint    idMaterialSpecular;
GLuint    idLightingPhong;

/* MVP */
camera    cam = camera(vec3(2, 2, 2), vec3(0, 0, 0), vec3(0, 1, 0));
mat4      transform = mat4::Identity();
mat4      projection = mat4::Identity();

State state;

/*
 * 88888888ba  88888888888 888b      88 88888888ba,   88888888888 88888888ba   
 * 88      "8b 88          8888b     88 88      `"8b  88          88      "8b  
 * 88      ,8P 88          88 `8b    88 88        `8b 88          88      ,8P  
 * 88aaaaaa8P' 88aaaaa     88  `8b   88 88         88 88aaaaa     88aaaaaa8P'  
 * 88""""88'   88"""""     88   `8b  88 88         88 88"""""     88""""88'    
 * 88    `8b   88          88    `8b 88 88         8P 88          88    `8b    
 * 88     `8b  88          88     `8888 88      .a8P  88          88     `8b   
 * 88      `8b 88888888888 88      `888 88888888Y"'   88888888888 88      `8b 
 */
const char* const vertex_shader = glsl(
  in vec3 vert;
  in vec3 vertNormal;

  uniform mat4 uMVPMatrix;
  uniform mat4 uMVMatrix;
  uniform mat4 uNormalMatrix;

  uniform vec3 light_position;
  uniform vec4 light_intensity;
  uniform vec4 ambient_intensity;
  uniform vec4 material_specular;
  uniform vec4 material_diffuse;
  uniform vec4 material_ambient;
  uniform uint lighting_phong;

  out vec4 vertColor;

  vec4 phong() {
    //  P is the vertex coordinate on body
    vec3 P = vec3(uMVMatrix * vec4(vert, 1));

    //  N is the object normal at P
    mat4 normalMatrix = transpose(inverse(uMVMatrix));
    vec3 N = normalize(vec3(normalMatrix * vec4(vertNormal, 0.0)));

    //  Light Position for light 0
    vec3 LightPos = light_position;

    //  L is the light vector
    vec3 L = normalize(LightPos - P);

    //  R is the reflected light vector R = 2(L.N)N - L
    vec3 R = reflect(-L, N);

    //  V is the view vector (eye at the origin)
    vec3 V = normalize(-P);

    //  Diffuse light intensity is cosine of light and normal vectors
    float Id = max(dot(L,N) , 0.0);

    //  Shininess intensity is cosine of light and reflection vectors to a power
    float Is = (Id>0.0) ? pow(max(dot(R,V) , 0.0), lighting_phong) : 0.0;

    //  Vertex color
    return ambient_intensity*material_ambient 
        + light_intensity*Id*material_diffuse 
        + light_intensity*Is*material_specular;
  }

  void main() {
    gl_Position =  uMVPMatrix * vec4(vert, 1.0);
    // vertColor = phong();// * 0.5*(gl_Position/gl_Position.w + 1.0);
    //vertColor = model * vec4(vertNormal, 1);
    vertColor = phong();
  }
);
const char* const fragment_shader = glsl(
  in vec4 vertColor;
  out vec4 finalColor;
  void main() {
    finalColor = vertColor;
  }
);

void renderScene() {
  mat4 mvp    = projection * (*cam.GetView()) * transform;

  // Not used at the moment, since our mat4::Inverse() doesn't pass tests
  mat4 normal = transform.Inverse().Transpose();

  glUniformMatrix4fv(idMVPMatrix, 1, GL_TRUE,
            (const float*)&mvp);
  glUniformMatrix4fv(idMVMatrix, 1, GL_TRUE,
            (const float*)&transform);
  glUniformMatrix4fv(idNormalMatrix, 1, GL_TRUE,
            (const float*)&normal);

  // Load lighting data
  glUniform3fv(idLightPosition, 1, 
            (const float*)&state.lighting.light_position);
  glUniform4fv(idLightIntensity, 1, 
            (const float*)&state.lighting.light_intensity);
  glUniform4fv(idAmbientIntensity, 1, 
            (const float*)&state.lighting.ambient_intensity);
  glUniform4fv(idMaterialAmbient, 1, 
            (const float*)&state.lighting.material_ambient);
  glUniform4fv(idMaterialDiffuse, 1, 
            (const float*)&state.lighting.material_diffuse);
  glUniform4fv(idMaterialSpecular, 1, 
            (const float*)&state.lighting.material_specular);
  glUniform1ui(idLightingPhong, state.lighting.phong);


  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
  glDrawElements(GL_TRIANGLES, state.render.num_indices, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
  glutSwapBuffers();
}

/*
 * 88           ,ad8888ba,         db         88888888ba,
 * 88          d8"'    `"8b       d88b        88      `"8b
 * 88         d8'        `8b     d8'`8b       88        `8b
 * 88         88          88    d8'  `8b      88         88
 * 88         88          88   d8YaaaaY8b     88         88
 * 88         Y8,        ,8P  d8""""""""8b    88         8P
 * 88          Y8a.    .a8P  d8'        `8b   88      .a8P
 * 88888888888  `"Y8888Y"'  d8'          `8b  88888888Y"'
 */
void loadModelIntoGL() {
  model::data m = state.render.model;
  state.render.num_indices = m.indices.size();
  uint num_v = m.vertices.size();

  // Build buffers
  vec3 vert_buf[m.vertices.size()];
  for(uint i = 0; i < m.vertices.size(); i++) {
    vert_buf[i] = m.vertices[i];
  }
  vec3 norm_buf[m.normals.size()];
  for(uint i = 0; i < m.normals.size(); i++) {
    if(state.render.flip_normals) {
      norm_buf[i] = -m.normals[i];
    } else {
      norm_buf[i] = m.normals[i];
    }
  }
  uint ind_buf[m.indices.size()];
  for(uint i = 0; i < m.indices.size(); i++) {
    ind_buf[i] = m.indices[i];
  }

  // Load vertices
  glBufferSubData(GL_ARRAY_BUFFER, 0, num_v*sizeof(vec3), vert_buf);

  // Load vertex normals
  glBufferSubData(GL_ARRAY_BUFFER, num_v*sizeof(vec3), num_v*sizeof(vec3), norm_buf);

  // Load vertex indices (representing triangular polygons)
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, state.render.num_indices*sizeof(uint),
                 ind_buf, GL_STATIC_DRAW);    

  // Update attrib pointers so opengl knows where vertices end and normals begin
  glVertexAttribPointer(locPosition, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)BUFFER_OFFSET(0));
  glVertexAttribPointer(locNormal,   3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)BUFFER_OFFSET(num_v*sizeof(vec3)));
}


/*
 * 88  88888888ba,    88           88888888888  
 * 88  88      `"8b   88           88           
 * 88  88        `8b  88           88           
 * 88  88         88  88           88aaaaa      
 * 88  88         88  88           88"""""      
 * 88  88         8P  88           88           
 * 88  88      .a8P   88           88           
 * 88  88888888Y"'    88888888888  88888888888  
 */
void idle() {
  guiMainIteration();

  if(state.heldkeys.a) {
    cam.Strafe(-CAMERA_SPEED);
    state.shouldUpdate = true;
  } else if(state.heldkeys.d) {
    cam.Strafe(CAMERA_SPEED);
    state.shouldUpdate = true;
  }

  if(state.heldkeys.w) {
    cam.Drive(-CAMERA_SPEED);
    state.shouldUpdate = true;
  } else if(state.heldkeys.s) {
    cam.Drive(CAMERA_SPEED);
    state.shouldUpdate = true;
  }

  if(state.heldkeys.q) {
    cam.Elevate(-CAMERA_SPEED);
    state.shouldUpdate = true;
  } else if(state.heldkeys.e) {
    cam.Elevate(CAMERA_SPEED);
    state.shouldUpdate = true;
  }

  if(state.newModelFilename != NULL) {
    std::cout << "New model!\n";
    loadModelFile(state.newModelFilename);
    state.newModelFilename = NULL;
    state.shouldReload = true;
    // reset(); // TODO
  }
  
  if(state.shouldReload) {
    state.shouldReload = false;
    std::cout << "Reloading model\n";
    loadModelIntoGL();
    state.shouldUpdate = true;
  }

  if(!state.shouldUpdate) {
    return;
  }

  if(state.mouse.vertical_rotation != 0 || state.mouse.horizontal_rotation != 0) {
    cam.RotateX(state.mouse.vertical_rotation);
    cam.RotateY(state.mouse.horizontal_rotation);
    state.mouse.vertical_rotation = state.mouse.horizontal_rotation = 0;
    std::cout << cam;
  }

  transform = mat4::Identity()
    .RotateX(state.transform.ax)
    .RotateY(state.transform.ay)
    .RotateZ(state.transform.az)
    .Scale(state.transform.s)
    .Translate(state.transform.dx, state.transform.dy, 0);

  state.shouldUpdate = false;

  glutPostRedisplay();
}

/*
 *   ,ad8888ba,   88888888ba    ad88888ba   
 *  d8"'    `"8b  88      "8b  d8"     "8b  
 * d8'            88      ,8P  Y8,          
 * 88             88aaaaaa8P'  `Y8aaaaa,    
 * 88             88""""""8b,    `"""""8b,  
 * Y8,            88      `8b          `8b  
 *  Y8a.    .a8P  88      a8P  Y8a     a8P  
 *   `"Y8888Y"'   88888888P"    "Y88888P"   
 */
void onPassiveMouseMove(int x, int y) {
  state.mouse.last_x = x;
  state.mouse.last_y = y;
  glutSetCursor(GLUT_CURSOR_INHERIT);
}

void onMouseMove(int x, int y) {
  state.mouse.horizontal_rotation += float(-state.mouse.last_x + x) * MOUSE_SENSITIVITY;
  state.mouse.vertical_rotation   += float( state.mouse.last_y - y) * MOUSE_SENSITIVITY;

  glutWarpPointer(state.window_width/2, state.window_height/2);
  state.mouse.last_x = state.window_width/2;
  state.mouse.last_y = state.window_height/2;

  state.shouldUpdate = true;
  glutSetCursor(GLUT_CURSOR_NONE);
}

void reshape(int width, int height) {
  int size = std::min(width, height);
  int x_off = (width-size)/2;
  int y_off = (height-size)/2;
  glViewport(x_off, y_off, size, size);
  state.window_width = width;
  state.window_height = height;
}

void onKeyDown(unsigned char key, int x, int y){
  if(key == 'w') {
    state.heldkeys.w = true;
  }
  if(key == 'a') {
    state.heldkeys.a = true;
  }
  if(key == 's') {
    state.heldkeys.s = true;
  }
  if(key == 'd') {
    state.heldkeys.d = true;
  }
  if(key == 'q') {
    state.heldkeys.q = true;
  }
  if(key == 'e') {
    state.heldkeys.e = true;
  }
}

void onKeyUp(unsigned char key, int x, int y) {
  if(key == 'w') {
    state.heldkeys.w = false;
  }
  if(key == 'a') {
    state.heldkeys.a = false;
  }
  if(key == 's') {
    state.heldkeys.s = false;
  }
  if(key == 'd') {
    state.heldkeys.d = false;
  }
  if(key == 'q') {
    state.heldkeys.q = false;
  }
  if(key == 'e') {
    state.heldkeys.e = false;
  }
}

void onSpecialDown(int key, int x, int y) {
  int mod = glutGetModifiers();

  if(mod & GLUT_ACTIVE_CTRL) {
    switch(key) {
    case GLUT_KEY_UP:
      state.transform.ax -= PI/36;
      break;
    case GLUT_KEY_DOWN:
      state.transform.ax += PI/36;
      break;
    case GLUT_KEY_RIGHT:
      state.transform.ay -= PI/36;
      break;
    case GLUT_KEY_LEFT:
      state.transform.ay += PI/36;
      break;
    default:
      return;
    }
  } else if(mod & GLUT_ACTIVE_SHIFT) {
    switch(key) {
    case GLUT_KEY_UP:
      state.transform.s += 0.1;
      break;
    case GLUT_KEY_DOWN:
      state.transform.s -= 0.1;
      break;
    case GLUT_KEY_RIGHT:
      state.transform.az -= PI/36;
      break;
    case GLUT_KEY_LEFT:
      state.transform.az += PI/36;
      break;
    default:
      return;
    }
  } else {
    switch(key) {
    case GLUT_KEY_UP:
      state.transform.dy += 0.1;
      break;
    case GLUT_KEY_DOWN:
      state.transform.dy -= 0.1;
      break;
    case GLUT_KEY_RIGHT:
      state.transform.dx += 0.1;
      break;
    case GLUT_KEY_LEFT:
      state.transform.dx -= 0.1;
      break;
    default:
      return;
    }
  }

  state.shouldUpdate = true;
}

/*
 * 88        88  888888888888  88  88           
 * 88        88       88       88  88           
 * 88        88       88       88  88           
 * 88        88       88       88  88           
 * 88        88       88       88  88           
 * 88        88       88       88  88           
 * Y8a.    .a8P       88       88  88           
 *  `"Y8888Y"'        88       88  88888888888  
 */
void reset() {
  transform = mat4::Identity();

  gui_set_light_pos( vec3(5.0, 5.0, 5.0));
  gui_set_I_light(   vec4(1.0, 1.0, 1.0));
  gui_set_I_ambient( vec4(1.0, 1.0, 1.0));
  gui_set_k_specular(vec4(1.0, 1.0, 1.0));
  gui_set_k_diffuse( vec4(221.0/255.0, 215.0/255.0, 152.0/255.0));
  gui_set_k_ambient( vec4(0.1, 0.1, 0.1));

  gui_set_phong(1);
  gui_set_move_mode(0);
}

void loadModelFile(char* filename) {
  try {
    state.render.model = model::read(filename);
    loadModelIntoGL();
  } catch(model::ParseException &e) {
    std::cerr << "Invalid OFF-file: \"" << e.what() << "\" on line " << e.line << std::endl;
  }
}

void setOrthographic() {
  float left,right,top,bottom,far,near;
  right = top = near = 5;
  left = bottom = far = -5;

  mat4 ST = mat4::Identity()
      .Translate(-(left+right)/(right-left), -(top+bottom)/(top-bottom), -(far+near)/(far-near))
      .Scale(2.0f/(right-left), 2.0f/(top-bottom), 2.0f/(far-near));

  projection = ST;
}

void setOblique() {
  float theta, psi;
  theta = psi = PI/4;

  mat4 H = mat4::Identity();
  H[2] = cos(theta)/sin(theta);
  H[6] = cos(psi)/sin(psi);

  setOrthographic();
  projection = projection * H;
}

void setPerspective(const float &far, const float &near, const float &fov) {
  mat4 P;

  float scale = 1.0/tan(fov / 360.0 * PI);

  P[0*4 + 0] = scale;
  P[1*4 + 1] = scale;
  P[2*4 + 2] = - far / (far - near);
  P[2*4 + 3] = - far * near / (far - near);
  P[3*4 + 2] = - 1;
  P[3*4 + 3] = 0;

  projection = P;
}

/*
 *  ad88888ba  88888888888 888888888888 88        88 88888888ba   
 * d8"     "8b 88               88      88        88 88      "8b  
 * Y8,         88               88      88        88 88      ,8P  
 * `Y8aaaaa,   88aaaaa          88      88        88 88aaaaaa8P'  
 *   `"""""8b, 88"""""          88      88        88 88""""""'    
 *         `8b 88               88      88        88 88           
 * Y8a     a8P 88               88      Y8a.    .a8P 88           
 *  "Y88888P"  88888888888      88       `"Y8888Y"'  88   
 */ 
void initGlut(int argc, char **argv) {
  /* Initialize glut */
  glutInit(&argc, argv);

  /* Display Mode 
      GLUT_DOUBLE together with glutSwapBuffers(); for double buffering */
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  /* Window Size */
  glutInitWindowSize(300, 300);
  glutInitContextProfile( GLUT_CORE_PROFILE );
  /* GL Version 
     Check with glxinfo | grep Open for supported version */
  glutInitContextVersion(3, 1);    

  /* Window label */
  glutCreateWindow("Assignment 1");
}


void initGL(void) {
  GLuint program;
  GLuint buffer;
  GLuint indexBuffer;
  GLuint vao;

  /* Setting up GL Extensions */
  glewExperimental = GL_TRUE; 
  glewInit();

  /* Create and initialize a program object with shaders */
  program = Shading::initProgram(vertex_shader, fragment_shader);

  /* installs the program object as part of current rendering state */
  glUseProgram(program);

  /* Creat a vertex array object */ 
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  
  /* Create buffer in the shared display list space and 
       bind it as GL_ARRAY_BUFFER */
  glGenBuffers( 1, &buffer);
  glBindBuffer( GL_ARRAY_BUFFER, buffer);
  glBufferData( GL_ARRAY_BUFFER, BUFFER_SIZE*sizeof(vec3)+BUFFER_SIZE*sizeof(vec3), NULL, GL_STATIC_DRAW);
    
  /* Create buffer in the shared display list space and 
       bind it as GL_ELEMENT_ARRAY_BUFFER */
  glGenBuffers( 1, &indexBuffer);
  glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
  
  /* Initialize attribute vPosition in program */
  locPosition = glGetAttribLocation( program, "vert");
  glEnableVertexAttribArray(locPosition);

  locNormal = glGetAttribLocation(program, "vertNormal");
  glEnableVertexAttribArray(locNormal);

  // normal = glGetAttribLocation( program, "vNormal");
  // glEnableVertexAttribArray(normal);
  // glVertexAttribPointer(normal, 3, GL_FLOAT, GL_FALSE, 3, (GLvoid*)BUFFER_OFFSET(3));

  idMVPMatrix        = glGetUniformLocation(program, "uMVPMatrix");
  idMVMatrix         = glGetUniformLocation(program, "uMVMatrix");
  idNormalMatrix     = glGetUniformLocation(program, "uNormalMatrix");
  idLightPosition    = glGetUniformLocation(program, "light_position");
  idLightIntensity   = glGetUniformLocation(program, "light_intensity");
  idAmbientIntensity = glGetUniformLocation(program, "ambient_intensity");
  idMaterialAmbient  = glGetUniformLocation(program, "material_ambient");
  idMaterialDiffuse  = glGetUniformLocation(program, "material_diffuse");
  idMaterialSpecular = glGetUniformLocation(program, "material_specular");
  idLightingPhong    = glGetUniformLocation(program, "lighting_phong");


  /* Set graphics attributes */
  glLineWidth(1.0);
  glPointSize(1.0);
  glClearColor(0.0, 0.0, 0.0, 0.0);

  //glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
}

int main(int argc, char *argv[]) {
  /* Initialization */
  initGlut(argc, argv);
  initGL();

  glutDisplayFunc(renderScene);
  glutIdleFunc(idle);
  glutKeyboardFunc(onKeyDown);
  glutKeyboardUpFunc(onKeyUp);
  glutSpecialFunc(onSpecialDown);
  glutReshapeFunc(reshape); 
  glutMotionFunc(onMouseMove);
  glutPassiveMotionFunc(onPassiveMouseMove);


  if(argc > 1) {
    state.newModelFilename = argv[1];
  }

  state.window_width  = glutGet(GLUT_WINDOW_WIDTH);
  state.window_height = glutGet(GLUT_WINDOW_HEIGHT);

  setPerspective(100, 0.1, 70);

  /* Initialize GUI */
  guiInit(&argc, argv);
  guiInitWindow("ass3gui.glade");

  reset(); // TODO
  // gui_set_flip_normals(FALSE);
  // gui_set_I_light(color);

  /* Loop for an infinitesimal while */
  glutMainLoop();

  return 0;
}
