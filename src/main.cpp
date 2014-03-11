#include "main.hpp"
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
#define glsl(x) "#version 140\n" #x
const char* const vertex_shader = glsl(
  in vec3 vPosition;

  uniform mat4 P;
  uniform mat4 T;
  uniform mat4 V;

  void main() {
    gl_Position =  P*V*T*vec4(vPosition, 1.0);
  }
);
const char* const fragment_shader = glsl(
  out vec4 fColor;

  void main() {
    fColor = vec4( 0.804, 0.416, 0.667, 1.0 );
    //fColor = vec4( 1.0, 0.0, 0.0, 1.0 );
  }
);

void renderScene() {
  glUniformMatrix4fv(idTransMat, 1, GL_TRUE,
            (const float*)&transform);
  glUniformMatrix4fv(idViewMat, 1, GL_TRUE,
            (const float*)cam.GetView());
  glUniformMatrix4fv(idProjMat, 1, GL_TRUE,
            (const float*)&projection);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
  glDrawArrays(GL_TRIANGLES, 0, vertexCount);
  glutSwapBuffers();
}

void loadModel(std::vector<vec3> vertices) {
  vec3 buf[vertices.size()];
  for(uint i = 0; i < vertices.size(); i++) {
    buf[i] = vertices[i];
  }
  vertexCount = vertices.size();

  /* Load it to the buffer data array */
  glBufferData(GL_ARRAY_BUFFER, sizeof(buf), buf, GL_STATIC_DRAW );
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
  //guiMainIteration();

  if(state.heldkeys.a) {
    cam.Strafe(CAMERA_SPEED);
    state.shouldUpdate = true;
  } else if(state.heldkeys.d) {
    cam.Strafe(-CAMERA_SPEED);
    state.shouldUpdate = true;
  }

  if(state.heldkeys.w) {
    cam.Drive(CAMERA_SPEED);
    state.shouldUpdate = true;
  } else if(state.heldkeys.s) {
    cam.Drive(-CAMERA_SPEED);
    state.shouldUpdate = true;
  }

  if(state.heldkeys.q) {
    cam.Elevate(CAMERA_SPEED);
    state.shouldUpdate = true;
  } else if(state.heldkeys.e) {
    cam.Elevate(-CAMERA_SPEED);
    state.shouldUpdate = true;
  }
  
  if(!state.shouldUpdate) {
    return;
  }

  state.mouse.vertical_rotation = std::max(float(-PI/2.0), std::min(float(PI/2.0), state.mouse.vertical_rotation));
  cam.SetAngles(state.mouse.horizontal_rotation, state.mouse.vertical_rotation);
  
  std::cout << "idle()" << std::endl;
  
  transform = mat4::Identity()
    .RotateX(state.transform.ax)
    .RotateY(state.transform.ay)
    .RotateZ(state.transform.az)
    .Scale(state.transform.s)
    .Translate(state.transform.dx, state.transform.dy, 0);

  std::cout << transform << std::endl;
  std::cout << cam << std::endl;
  
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
      state.transform.ax += 3.141592/36;
      break;
    case GLUT_KEY_DOWN:
      state.transform.ax += 3.141592/36;
      break;
    case GLUT_KEY_RIGHT:
      state.transform.ay -= 3.141592/36;
      break;
    case GLUT_KEY_LEFT:
      state.transform.ay += 3.141592/36;
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
      state.transform.az -= 3.141592/36;
      break;
    case GLUT_KEY_LEFT:
      state.transform.az += 3.141592/36;
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
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
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
  GLuint loc;
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
  
  /* Initialize attribute vPosition in program */
  loc = glGetAttribLocation( program, "vPosition");
  glEnableVertexAttribArray(loc);
  glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)BUFFER_OFFSET(0));

  // normal = glGetAttribLocation( program, "vNormal");
  // glEnableVertexAttribArray(normal);
  // glVertexAttribPointer(normal, 3, GL_FLOAT, GL_FALSE, 3, (GLvoid*)BUFFER_OFFSET(3));


  idTransMat = glGetUniformLocation(program, "T");
  idViewMat  = glGetUniformLocation(program, "V");
  idProjMat  = glGetUniformLocation(program, "P");

  /* Set graphics attributes */
  glLineWidth(1.0);
  glPointSize(1.0);
  glClearColor(0.0, 0.0, 0.0, 0.0);

  glEnable(GL_CULL_FACE);
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
    try {
      std::vector<vec3> vertices = model::read(argv[1]);
      loadModel(vertices);
    } catch(model::ParseException &e) {
      std::cerr << "Invalid OFF-file: \"" << e.what() << "\" on line " << e.line << std::endl;
    }
  }

  state.window_width  = glutGet(GLUT_WINDOW_WIDTH);
  state.window_height = glutGet(GLUT_WINDOW_HEIGHT);

  setPerspective(100, 0.1, 70);
  state.shouldUpdate = true;

  /* Loop for an infinitesimal while */
  glutMainLoop();

  return 0;
}
