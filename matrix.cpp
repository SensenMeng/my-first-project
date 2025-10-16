#include <iostream>
#include <vector>
#include <cmath>
//#include <iomanip>

using namespace std;

void iMa(vector<vector<double>> & matrix);
void oMa(const vector<vector<double>> & matrix);

vector<vector<double>> solve(const vector<vector<double>> & matrix);

vector<vector<double>> originMinor(const vector<vector<double>> & matrix, int row, int column);
double Minor(const vector<vector<double>> & matrix, int row, int column);
double alg(const vector<vector<double>> & matrix, int row, int column);
double det(const vector<vector<double>> & matrix);

vector<vector<double>> accMa(const vector<vector<double>> & matrix);
vector<vector<double>> inverMa(const vector<vector<double>> & matrix);
int rankMa(const vector<vector<double>> & matrix);

vector<vector<double>> addMa(const vector<vector<double>> & matrix1, const vector<vector<double>> & matrix2);
vector<vector<double>> minusMa(const vector<vector<double>> & matrix1, const vector<vector<double>> & matrix2);
vector<vector<double>> multiMa(const vector<vector<double>> & matrix, double k);
vector<vector<double>> multiMa(double k, const vector<vector<double>> & matrix);
vector<vector<double>> multiMa(const vector<vector<double>> & matrix1, const vector<vector<double>> & matrix2);

vector<vector<double>> transMa(const vector<vector<double>> & matrix);
vector<vector<double>> stepize(const vector<vector<double>> & matrix);
vector<vector<double>> rowSimplify(const vector<vector<double>> & matrix);

void minusrow(vector<vector<double>> & matrix, int target, int sub, double k = 1);
void minuscol(vector<vector<double>> & matrix, int target, int sub, double k = 1);
void exrow(vector<vector<double>> & matrix, int a, int b);
void excol(vector<vector<double>> & matrix, int a, int b);
void multirow(vector<vector<double>> & matrix, int row, double k);
void multicol(vector<vector<double>> & matrix, int column, double k);

double fixZero(double value);

int main()
{
    cout << "1. det             2. inverse         3. add             4. minus\n";
    cout << "5. multi1          6. multi2          7. transform       8. accompany\n";
    cout << "9. alg             10. originMinor    11. minor          12. rank\n";
    cout << "13. stepize        14. rowSimplify    15. solve\n";
    int mode, k, row, column;
    vector<vector<double>> target1, target2;
    while (1)
    {
        cout << "----------------------------------------" << endl;
        cout << "Enter the mode: ";
        cin >> mode;
        switch(mode)
        {
            case 1:
                iMa(target1);
                cout << "----------------------------------------" << endl;
                cout << det(target1) << endl;break;
            case 2:
                iMa(target1);
                oMa(inverMa(target1));break;
            case 3:
                iMa(target1);
                iMa(target2);
                oMa(addMa(target1, target2));break;
            case 4:
                iMa(target1);
                iMa(target2);
                oMa(minusMa(target1, target2));break;
            case 5:
                cout << "Enter k: ";
                cin >> k;
                iMa(target1);
                oMa(multiMa(k, target1));break;
            case 6:
                iMa(target1);
                iMa(target2);
                oMa(multiMa(target1, target2));break;
            case 7:
                iMa(target1);
                oMa(transMa(target1));break;
            case 8:
                iMa(target1);
                oMa(accMa(target1));break;
            case 9:
                iMa(target1);
                cout << "Enter the row and column you want as A's: ";
                cin >> row >> column;
                cout << "----------------------------------------" << endl;
                cout << alg(target1, row, column) << endl;break;
            case 10:
                iMa(target1);
                cout << "Enter the row and column you want as A's: ";
                cin >> row >> column;
                oMa(originMinor(target1, row, column));break;
            case 11:
                iMa(target1);
                cout << "Enter the row and column you want as A's: ";
                cin >> row >> column;
                cout << "----------------------------------------" << endl;
                cout << Minor(target1, row, column) << endl;break;
            case 12:
                iMa(target1);
                cout << "----------------------------------------" << endl;
                cout << "rank: " << rankMa(target1) << endl;break;
            case 13:
                iMa(target1);
                oMa(stepize(target1));break;
            case 14:
                iMa(target1);
                oMa(rowSimplify(target1));break;
            case 15:
                iMa(target1);
                oMa(solve(target1));break;
            default:
                cout << "Wrong number, please try again!" << endl;break;
        }
    }
    return 0;
}

void iMa(vector<vector<double>> & matrix)
{
    cout << "Enter the row and column: ";
    int row, column;
    cin >> row >> column;
    matrix.resize(row, vector<double>(column));  //重新分配vector的大小，防止越界访问
    for(int i = 0; i < row; i++)
        for(int j = 0; j < column; j++)
            cin >> matrix[i][j];
}

void oMa(const vector<vector<double>> & matrix)
{
    cout << "----------------------------------------" << endl;
    for(auto pos = matrix.begin(); pos != matrix.end(); pos++)
    {
        for(auto subpos = (*pos).begin(); subpos != (*pos).end(); subpos++)
            cout << *subpos << " ";
        cout << "\n";
    }
}

vector<vector<double>> solve(const vector<vector<double>> & matrix)
{
    vector<vector<double>> A, Ab, result;
    Ab = rowSimplify(matrix);
    A.resize(size(matrix), vector<double>(size(matrix[0]) - 1));
    result.resize(size(matrix), vector<double>(1));
    
    return result;
}

vector<vector<double>> originMinor(const vector<vector<double>> & matrix, int row, int column)
{
    vector<vector<double>> matrix1 = matrix;
    matrix1.erase(matrix1.begin() + row);
    for(auto pos = matrix1.begin(); pos != matrix1.end(); pos++)
        (*pos).erase((*pos).begin() + column);
    return matrix1;
}

double Minor(const vector<vector<double>> & matrix, int row, int column)
{
    return det(originMinor(matrix, row, column));
}

double alg(const vector<vector<double>> & matrix, int row, int column)
{
    return pow(-1, row + column) * Minor(matrix, row, column);
}

double det(const vector<vector<double>> & matrix)
{
    if (matrix.size() != matrix[0].size())
    {
        cerr << "Please check your matrix again!" << endl;
        return -1;
    }
    if (matrix.size() == 1)
        return matrix[0][0];
    double result = 0;
    int i = 0;
    for(auto pos = matrix[0].begin(); pos != matrix[0].end(); pos++)
    {
        result += pow(-1, i) * det(originMinor(matrix, 0, i)) * matrix[0][i];
        i++;
    }
    return result;
}

vector<vector<double>> accMa(const vector<vector<double>> & matrix)
{
    if (matrix.size() != matrix[0].size())
    {
        cout << "Please check your matrix again!" << endl;
        return matrix;
    }
    vector<vector<double>> matrix1 = matrix;
    for(int i = 0; i < matrix.size(); i++)
        for(int j = 0; j < matrix.size(); j++)
        {
            matrix1[i][j] = alg(matrix, j, i);
            matrix1[i][j] = fixZero(matrix1[i][j]);
        }
    return matrix1;
}

vector<vector<double>> inverMa(const vector<vector<double>> & matrix)
{
    double determinant = det(matrix);
    if (fabs(determinant) < 1e-9)
    {
        cerr << "This matrix is not inverseable." << endl;
        return matrix;
    }
    vector<vector<double>> result;
    result.resize(size(matrix), vector<double>(size(matrix[0])));
    result = multiMa(1.0 / det(matrix), accMa(matrix));
    for(int i = 0; i < matrix.size(); i++)
        for(int j = 0; j < matrix.size(); j++)
        {
            result[i][j] = fixZero(result[i][j]);
        }
    return result;
}

vector<vector<double>> addMa(const vector<vector<double>> & matrix1, const vector<vector<double>> & matrix2)
{
    if (size(matrix1) != size(matrix2) || size(matrix1[0]) != size(matrix2[0]))
    {
        cerr << "They are not Homo matrix!" << endl;
        return matrix1;
    }
    vector<vector<double>> result;
    result.resize(size(matrix1), vector<double>(size(matrix1[0])));
    for(int i = 0; i < size(matrix1); i++)
        for(int j = 0; j < size(matrix2[0]); j++)
            result[i][j] = matrix1[i][j] + matrix2[i][j];
    return result;
}

vector<vector<double>> minusMa(const vector<vector<double>> & matrix1, const vector<vector<double>> & matrix2)
{
    if (size(matrix1) != size(matrix2) || size(matrix1[0]) != size(matrix2[0]))
    {
        cerr << "They are not Homo matrix!" << endl;
        return matrix1;
    }
    vector<vector<double>> result;
    result.resize(size(matrix1), vector<double>(size(matrix1[0])));
    for(int i = 0; i < size(matrix1); i++)
        for(int j = 0; j < size(matrix2[0]); j++)
            result[i][j] = matrix1[i][j] - matrix2[i][j];
    return result;
}

vector<vector<double>> multiMa(const vector<vector<double>> & matrix, double k)
{
    vector<vector<double>> result;
    result.resize(size(matrix), vector<double>(size(matrix[0])));
    for(int i = 0; i < size(matrix); i++)
        for(int j = 0; j < size(matrix[0]); j++)
            result[i][j] = k * matrix[i][j];
    return result;
}

vector<vector<double>> multiMa(double k, const vector<vector<double>> & matrix)
{
    return multiMa(matrix, k);
}

vector<vector<double>> multiMa(const vector<vector<double>> & matrix1, const vector<vector<double>> & matrix2)
{
    if(size(matrix1[0]) != size(matrix2))
    {
        cerr << "They can't multiply!" << endl;
        return matrix1;
    }
    vector<vector<double>> result;
    result.resize(size(matrix1), vector<double>(size(matrix2[0])));
    for (int i = 0; i < size(matrix1); i++)
        for(int j = 0; j < size(matrix2[0]); j++)
            for(int k = 0; k < size(matrix1[0]); k++)
                result[i][j] += matrix1[i][k] * matrix2[k][j];
    return result;
}

vector<vector<double>> transMa(const vector<vector<double>> & matrix)
{
    vector<vector<double>> result;
    result.resize(size(matrix[0]), vector<double>(size(matrix)));
    for (int i = 0; i < size(matrix); i++)
        for (int j = 0; j < size(matrix[0]); j++)
            result[j][i] = matrix[i][j];
    return result;
}

vector<vector<double>> stepize(const vector<vector<double>> & matrix)
{
    vector<vector<double>> matrix1 = matrix;
    int rows = size(matrix1), cols = size(matrix1[0]);
    int pivotRow = 0;
    for(int i = 0; i < cols; i++)
    {
        int noZeroRow = -1;
        for(int j = pivotRow; j < rows; j++)
            if(fabs(matrix1[j][i]) > 1e-9)
            {
                noZeroRow = j;
                break;
            }
        if (noZeroRow == -1)
            continue;
        multirow(matrix1, noZeroRow, 1.0 / matrix1[noZeroRow][i]);
        exrow(matrix1, noZeroRow, pivotRow);
        for(int j = pivotRow + 1; j < rows; j++)
        {
            minusrow(matrix1, j, pivotRow, matrix1[j][i]);
        }
        pivotRow++;
    }
    return matrix1;
}

vector<vector<double>> rowSimplify(const vector<vector<double>> & matrix)
{
    vector<vector<double>> matrix1 = stepize(matrix);
    int rank = rankMa(matrix);
    for (int i = 0; i < rank - 1; i++)
    {
        int nextZeroCol = 0;
        for(int j = 0; j < size(matrix1[0]); j++)
            if(matrix1[i + 1][j])
            {
                nextZeroCol = j;
                break;
            }
        for(int j = 0; j < i + 1; j++)
            minusrow(matrix1, j, i + 1, matrix1[j][nextZeroCol]);
    }
    return matrix1;
}

int rankMa(const vector<vector<double>> & matrix)
{
    vector<vector<double>>matrix1 = stepize(matrix);
    //oMa(matrix1);
    int rank = 0;
    for (int i = 0; i < size(matrix1); i++)
        for(int j = 0; j < size(matrix1[0]); j++)
            if(matrix1[i][j])
            {
                rank++;
                break;
            }
    return rank;
}

void minusrow(vector<vector<double>> & matrix, int target, int sub, double k)
{
    for(int i = 0; i < size(matrix[0]); i++)
    {
        matrix[target][i] = matrix[target][i] - matrix[sub][i] * k;
        matrix[target][i] = fixZero(matrix[target][i]);
    }
}

void minuscol(vector<vector<double>> & matrix, int target, int sub, double k)
{
    for(int i = 0; i < size(matrix); i++)
    {
        matrix[i][target] = matrix[i][target] - matrix[i][sub] * k;
        matrix[i][target] = fixZero(matrix[i][target]);
    }
}

void exrow(vector<vector<double>> & matrix, int a, int b)
{
    for(int i = 0; i < size(matrix[0]); i++)
        swap(matrix[a][i], matrix[b][i]);
}

void excol(vector<vector<double>> & matrix, int a, int b)
{
    for(int i = 0; i < matrix.size(); i++) 
        swap(matrix[i][a], matrix[i][b]);
    
}

void multirow(vector<vector<double>> & matrix, int row, double k)
{
    for(int i = 0; i < size(matrix[0]); i++)
    {
        matrix[row][i] = matrix[row][i] * k;
        matrix[row][i] = fixZero(matrix[row][i]);
    }
}

void multicol(vector<vector<double>> & matrix, int column, double k)
{
    for(int i = 0; i < size(matrix); i++)
    {
        matrix[i][column] = matrix[i][column] * k;
        matrix[i][column] = fixZero(matrix[i][column]);
    }
}

double fixZero(double value) 
{
    const double eps = 1e-9;  // 极小值阈值
    return (fabs(value) < eps) ? 0.0 : value;
}