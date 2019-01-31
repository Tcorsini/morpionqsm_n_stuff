#ifndef RECTANGULAR_BOARD_HPP
#define RECTANGULAR_BOARD_HPP

namespace timGames {
  enum direction4 {UP = 0, RIGHT, DOWN, LEFT};
  enum direction8 {N = 0, NE, E, ES, S, SW, W, WN};

  enum direction8 dir4_to_dir8(enum direction4 d);
  enum direction4 dir8_to_dir4(enum direction8 d);
  //not a template, only contains all definitions of lines etc...
  class RectangularBoardAbstract {
    //private:
  protected:
    RectangularBoardAbstract(int lines, int columns):
      lines(lines), columns(columns), table_size(lines*columns)
    {
      if (lines <= 0 || columns <= 0)
	throw "Wrong column/lines value when initializing a RectangularBoard";
    }
  public:
    const int lines; //lignes
    const int columns; //colonnes
    const int table_size;
    inline bool is_pos_valid(int pos_piece) const {return (pos_piece >= 0 &&
						     pos_piece < table_size);}
    int calculate_pos_board(int line, int col) const { return line * columns + col; }
    inline int get_line(int id) const { return id/columns; }
    inline int get_column(int id) const { return id % columns; }

    virtual ~RectangularBoardAbstract() {}
    inline int get_max_line() const { return lines; }
    inline int get_max_column() const { return columns; }
    int adj_id(int id, enum direction4 dir) const;
    int adj_id(int id, enum direction8 dir) const;
  };
  
  /*
    Piece doit avoir :
    -Un constructeur par défaut
    -Un opérateur d'affectation valide 
    (plusieurs cases sont instanciées et copiées selon des valeurs)
    -Une valeur pratique par défaut
   */
  template <class Piece = int>
  class RectangularBoard : public RectangularBoardAbstract {
  private:
    Piece *T; //tableau
  public:
    int linesizeoneway(int id,
		       int (*next_tile) (const RectangularBoardAbstract&, int),
		       bool (*stop) (int occur,
				     const Piece& original_value,
				     const Piece& current_value)) const;
    /*
    int linesize(int id, int (*left) (const RectangularBoard&, int),
		 int (*right) (const RectangularBoard&, int),
		 bool max_line_size = false) const;*/
    bool put_piece(int pos_piece, Piece& value_piece);
    const Piece& get_piece(int pos_piece) const;
    Piece& operator[] (int i) { return T[i]; }
    const Piece& operator[] (int i) const { return T[i]; }
    /*
    int nb_horizontal(int pos, bool max_line_size = false) const; //12
    int nb_vertical(int pos, bool max_line_size = false) const; //|
    int nb_diag_dr(int pos, bool max_line_size = false) const; //¹2
    int nb_diag_ur(int pos, bool max_line_size = false) const; //1²*/
    
    RectangularBoard(int lines, int columns, const Piece& default_value):
      RectangularBoardAbstract(lines, columns)
    {
      T = new Piece[table_size];
      for (int i = 0; i < table_size; i++)
	T[i] = default_value;
    }
    virtual ~RectangularBoard() {
      delete[] T;
    }
  };

  template <class Piece>
  int RectangularBoard<Piece>::
  linesizeoneway(int id,
		 int (*next_tile) (const RectangularBoardAbstract&, int),
		 bool (*stop) (int occur, const Piece& original_value,
			       const Piece& current_value)) const
  {
    if (!is_pos_valid(id))
      throw "the given position is not valid";
    int i = -1;
    int current_pos = id;
    const Piece& original_value = get_piece(id);
    const Piece* p_current_value = &original_value;
    do {
      i += 1;
      current_pos = next_tile(*this, current_pos);
    }
    while (is_pos_valid(current_pos) &&
	   !stop(i, original_value, 
		 *(p_current_value = &get_piece(current_pos))));
    return i;
  }

  template <class Piece>
  bool RectangularBoard<Piece>::
  put_piece(int pos_piece, Piece& value_piece) {
    if (!is_pos_valid(pos_piece))
      return false;
    T[pos_piece] = value_piece;
    return true;
  }

  template <class Piece>
  const Piece& RectangularBoard<Piece>::
  get_piece(int pos_piece) const {
    if (!is_pos_valid(pos_piece))
      throw "Invalid id, should not happen";
    return T[pos_piece];
  }
  
}
#endif
