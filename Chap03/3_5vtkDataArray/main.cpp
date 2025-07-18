#include <vtkSmartPointer.h>
#include <vtkFloatArray.h>

/*   内存地址方向 →
+---------+---------+---------+---------+---------+---------+
| Tuple0  | Tuple1  | Tuple2  | Tuple3  | ...     | TupleN  |
+---------+---------+---------+---------+---------+---------+
| C0 C1 C2| C0 C1 C2| C0 C1 C2| C0 C1 C2| ...     | C0 C1 C2|
+---------+---------+---------+---------+---------+---------+
*/

int main()
{
   vtkSmartPointer<vtkFloatArray> array = vtkSmartPointer<vtkFloatArray>::New();

   array->SetNumberOfComponents(1);
   array->SetNumberOfTuples(10);

   //第5个元组，第0个分量
   array->SetComponent(5,0,100);

   //第1个元组，第0个分量,有SetTuple
   array->SetTuple1(1,50);

   double b=array->GetComponent(5,0);
   std::cout<<"b="<<b<<std::endl;

   double c=array->GetTuple1(1);
   std::cout<<"c="<<c<<std::endl;

   return 0;
}