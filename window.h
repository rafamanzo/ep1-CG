class Window{
  public:
    Window(VectorField);
    void loop();
    static void plot_vectors();
    static void resize(int width, int height);
    static void idle(void);
  private:
    VectorField _vf;
};
