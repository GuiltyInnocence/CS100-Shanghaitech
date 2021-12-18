#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <map>
using string=std::string;
// width of normal column and the row index column
const int DEFAULT_COLUMN_WIDTH = 7;
const int DEFAULT_ROW_IDX_WIDTH = 4;

// forward declaration of derived classes
class NumberSpreadSheetCell;
class StringSpreadSheetCell;

// types of spreadsheet cells
enum CellType { Number, String };

// The base SpreadSheetCell class 
class SpreadSheetCell{
public:
    // constructors and destructors.
    SpreadSheetCell(CellType ctp):m_type(ctp){};
//    ~SpreadSheetCell()=default;

    // output the content of cell
    friend std::ostream& operator<<(std::ostream& os, const SpreadSheetCell& cell);

    // comparsion between two cells
    virtual bool operator<(const SpreadSheetCell& that) const=0;

    // get the type of this cell, returns either CellType::Number or CellType::String
    CellType GetType() const {
        return m_type;
    }
protected:
    CellType m_type; // stores the type of the cell (either CellType::Number or CellType::String)
};


// The `NumberSpreadSheetCell` class, which content is a double
class NumberSpreadSheetCell : public SpreadSheetCell {
public:
    // Your own implementation here
    NumberSpreadSheetCell(double ge): SpreadSheetCell(CellType::Number),value(ge){};
    bool operator <(const SpreadSheetCell& that) const override{
        if(that.GetType()==CellType::String)return true;
        const auto ptr = (const NumberSpreadSheetCell*)(&that);
        return this->value<ptr->getvalue();
    }
    double getvalue()const {return value;}
private:
    double value;
};


// The `StringSpreadSheetCell` class, which content is a string
class StringSpreadSheetCell : public SpreadSheetCell {
public:
    // Your own implementation here
    StringSpreadSheetCell(string ge): SpreadSheetCell(CellType::String),value(ge){};
    //todo:std::move here, slow
    bool operator <(const SpreadSheetCell& that) const override{
        if(that.GetType()==CellType::Number)return false;
        const auto ptr = (const StringSpreadSheetCell*)(&that);
        return this->value<ptr->getvalue();
    }
    string getvalue() const{return value;}
    //todo:std::move here, slow
private:
    string value;
};

std::ostream& operator<<(std::ostream& os, const SpreadSheetCell& cell){
    switch (cell.GetType()) {
        case CellType::Number:
            os<<std::setprecision(3)<<((const NumberSpreadSheetCell*)(&cell))->getvalue();
            break;
        case CellType::String:
            os<<((const StringSpreadSheetCell*)(&cell))->getvalue();
            break;
    }
    return os;
}

class SpreadSheet {
public:
    // constructors and destructors
    SpreadSheet(int rows, int cols);
    ~SpreadSheet();

    // "hide" a row or column in this sheet, hidden row or column 
    // will not be shown in "ExportSheet" function
    void HideRow(int row);
    void HideColumn(int col);

    // re-show a hidden row or column in this sheet.
    // If the given row is not hidden, this does nothing.
    void ShowRow(int row);
    void ShowColumn(int col);

    // set a the pointer at (row, col) to `cell`, 
    // if there is already be a cell, delete it and reset it to `cell`
    void UpdateCell(int row, int col, SpreadSheetCell* cell);

    /* print the sheet to the ostream `os`. You may assume that `os' is std::cout.
     * Each column has width = DEFAULT_COLUMN_WIDTH
     * It's guaranteed that length of all cell contents are less than DEFAULT_COLUMN_WIDTH
     * The width of the column of ROW INDEX has width = DEFAULT_ROW_IDX_WIDTH
     * row index and column index are all ints which starts from 1.
     * If your implementation is correct, the output of given "main" function will be similar to:
     *     |      1      2      3      4
     * ---------------------------------
     *    1|  0.658   qufk    vry   3.43
     *    2|     ld   fdkr    omx  0.892
     *    3|    mlg   uqpb   4.91      r
     *    4|   wneo   4.49   atdh   itbf
     */
    void ExportSheet(std::ostream& os);

    // PROBLEM 3: Sort all rows by the value in `col`, in accending order, and number < string < nullptr.
    void SortByColumn(int col);

private:
    std::vector<std::vector<SpreadSheetCell*>> m_cells;
    std::map<int,bool> mr,mc;
    // Add your own private variables and functions here
};

// PROBLEM 3: A functor class for sorting. It should have an operator() that takes 2 parameters.
class ColumnComparator {
public:
    ColumnComparator(const int col):scol(col){};
    bool operator () (std::vector<SpreadSheetCell*>& coa,std::vector<SpreadSheetCell*>& cob) const{
        if(cob[scol]== nullptr)return true;
        if(coa[scol]== nullptr)return false;
        return *coa[scol]<*cob[scol];
    }
private:
    int scol;
};

SpreadSheet::SpreadSheet(int rows, int cols){
    for (int j = 0; j < cols; j++)
        mc[j]= false;
    for(int i=0;i<rows;i++) {
        mr[i]=false;
        m_cells.emplace_back(std::vector<SpreadSheetCell*>(cols,nullptr));
    }
}

SpreadSheet::~SpreadSheet(){
    for(auto &i:m_cells)
        for(auto &j:i){
            delete(j);
        }
}

void SpreadSheet::HideRow(int row){mr[row-1]= true;}

void SpreadSheet::HideColumn(int col){mc[col-1]= true;}

void SpreadSheet::ShowRow(int row){mr[row-1]= false;}

void SpreadSheet::ShowColumn(int col){mc[col-1]= false;}

void SpreadSheet::UpdateCell(int row, int col, SpreadSheetCell* cell){
    if(m_cells.empty() || row>m_cells.size() || col>m_cells[0].size())return;
    if(m_cells[row-1][col-1]!= nullptr){
        delete(m_cells[row-1][col-1]);
    }
    m_cells[row-1][col-1]=cell;
}

void SpreadSheet::ExportSheet(std::ostream& os){
    os<<std::setw(DEFAULT_ROW_IDX_WIDTH+1)<<'|';
    for(int j=0;j<m_cells[0].size();j++) {
        if(mc[j])continue;
        os << std::setw(DEFAULT_COLUMN_WIDTH)<<j+1;
    }
    os<<std::endl;
    os<<std::string(DEFAULT_ROW_IDX_WIDTH+1,'-');
    for(int j=0;j<m_cells[0].size();j++) {
        if(mc[j])continue;
        os<<std::string(DEFAULT_COLUMN_WIDTH,'-');
    }
    os<<std::endl;
    for(int i=0;i<m_cells.size();i++){
        if(mr[i])continue;
        os<<std::setw(DEFAULT_ROW_IDX_WIDTH)<<i+1<<'|';
        for(int j=0;j<m_cells[i].size();j++) {
            if(mc[j])continue;
            if(m_cells[i][j]== nullptr)
                os << std::string(DEFAULT_COLUMN_WIDTH,' ');
            else
                os << std::setw(DEFAULT_COLUMN_WIDTH) << *m_cells[i][j];
        }
        os<<std::endl;
    }
}

void SpreadSheet::SortByColumn(int col){
    std::sort(m_cells.begin(),m_cells.end(),ColumnComparator(col-1));
}

void testcell(){
    std::vector<SpreadSheetCell*> cells;
    cells.push_back(new NumberSpreadSheetCell(1.5333));
    cells.push_back(new NumberSpreadSheetCell(2.0));
    cells.push_back(new StringSpreadSheetCell("abc"));
    cells.push_back(new StringSpreadSheetCell("bbb"));
    std::cout << std::boolalpha << (*(cells[0]) < *(cells[1])) << std::endl;
// true (1.5333 < 2.0)
    std::cout << std::boolalpha << (*(cells[1]) < *(cells[0])) << std::endl;
// false (2.0 > 1.5333)
    std::cout << std::boolalpha << (*(cells[2]) < *(cells[3])) << std::endl;
// true ("abc" < "bbb")
    std::cout << std::boolalpha << (*(cells[3]) < *(cells[2])) << std::endl;
// false ("bbb" > "abc")
    std::cout << std::boolalpha << (*(cells[0]) < *(cells[3])) << std::endl;
// true (numbers < strings)
    std::cout << std::boolalpha << (*(cells[3]) < *(cells[0])) << std::endl;
// false (strings > numbers)
    std::cout << (*cells[0]) << std::endl;
// 1.53 (precision = 3)
    std::cout << (*cells[2]) << std::endl;
// abc (just print it)
    std::cout << cells[0]->GetType() << std::endl;
// 0 (CellType::Number)
    std::cout << cells[2]->GetType() << std::endl;
// 1 (CellType::String)
}
int main(){
//    testcell();
    srand(time(NULL));
    SpreadSheet sheet(4, 4);
    for (int i = 1; i <= 4; i++)
    {
        for (int j = 1; j <= 4; j++)
        {
            if (rand() < 0.5f * RAND_MAX)
                sheet.UpdateCell(i, j, new NumberSpreadSheetCell((double)rand() / double(RAND_MAX) * 5.0f));
            else 
            {
                std::string s;
                for(int k = 0; k < 1 + rand()%5; k++)
                    s += ('a' + rand() % 26);
                sheet.UpdateCell(i, j, new StringSpreadSheetCell(s));
            }
        }
    }
    sheet.ExportSheet(std::cout);
    sheet.SortByColumn(1);
    sheet.ExportSheet(std::cout);
}
