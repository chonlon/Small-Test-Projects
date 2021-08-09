//
// Created by lon on 2021/8/9.
//

#ifndef MINE_OCCT_DEMO_STEPREADER_HPP
#define MINE_OCCT_DEMO_STEPREADER_HPP

auto dumpLabelName (const TDF_Label& label, std::ostream& os,std::string attribute) -> std::ostream& {
  Handle(TDataStd_Name)  labelName;
  label.FindAttribute(TDataStd_Name::GetID(), labelName);
  os << attribute;
  labelName->Dump(os);
  os << '\n';
  return os;
};

class StepReader {
public:
    StepReader(std::string_view file_name) : file_name_(file_name) {

    }

    std::ostream &print(std::ostream& os) const {
      auto root_label = doc_handle_->Main();
      auto shape_tool = XCAFDoc_DocumentTool::ShapeTool(root_label);
      auto color_tool = XCAFDoc_DocumentTool::ColorTool(root_label);



      os << "\n\n===========dumping object: " << file_name_ << "==================\n";
      if(print_base_)  {
        auto base_label = shape_tool->BaseLabel();

        os << "\n\n-------------dumping base label---------------\n";
        {// base label name
          dumpLabelName(base_label, os,"base label name : ");
        }

        {// base label children
          int count = 0;
          for(TDF_ChildIterator it{base_label}; it.More(); it.Next()) {
            ++count;
            TDF_Label child_label = it.Value();
            TopoDS_Shape sub_shape = shape_tool->GetShape(child_label);

            if(!sub_shape.IsNull()) {
              os << "\nsub shape:\n\t";
              dumpLabelName(child_label, os,"sub label name: ");
              os << "\tshape json:\n\t\t";
              sub_shape.DumpJson(os);
              os << '\n';
            }
          }
          os << "\t---count: " << count << "---\n";
        }

        os << "\n\n--------------dumping free labels------------\n";
        {
          TDF_LabelSequence free_labels;
          shape_tool->GetFreeShapes(free_labels);
          auto size = free_labels.Size();

          for(TDF_LabelSequence::Iterator it(free_labels); it.More(); it.Next()) {
            TDF_Label child_free_label = it.Value();
            TopoDS_Shape sub_shape = shape_tool->GetShape(child_free_label);
            if(sub_shape.IsNull())
              continue;
            dfsTrSubLabel(child_free_label, os, shape_tool);
          }
        }
      }

      return os;
    }

    void dfsTrSubLabel(const TDF_Label& label, std::ostream& os, Handle(XCAFDoc_ShapeTool)& shape_tool ) const {
      dumpLabelName(label, os,"free label:");
      if(label.HasChild()) {
        for(TDF_ChildIterator it(label); it.More(); it.Next()) {
          dfsTrSubLabel(it.Value(), os, shape_tool);
        }

      } else {
        TopoDS_Shape sub_shape = shape_tool->GetShape(label);
        sub_shape.DumpJson(os);
        os<< '\n';
      }
    }
    bool parse() {
      STEPCAFControl_Reader reader;

      reader.SetColorMode(Standard_True);
      reader.SetNameMode(Standard_True);
      reader.SetLayerMode(Standard_True);

      IFSelect_ReturnStatus status = reader.ReadFile(file_name_.data());
      if(status != IFSelect_RetDone) {
        std::cout << "read file failed! which: " << file_name_;
        return false;
      }

      Handle(TDocStd_Application) app = new TDocStd_Application();
      app->NewDocument("MDTV-XCAF", doc_handle_);// 这里的format是什么//在TDocStd_Document构造函数中没有说明
      reader.Transfer(doc_handle_);
      return true;
    }
private:


    bool print_color_ = true;
    //    bool print_shape_ = true;
    bool print_base_ = true;
    bool print_freedom_ = true;
    std::string_view file_name_;
    Handle(TDocStd_Document) doc_handle_;
};
std::ostream &operator<<(std::ostream& os, StepReader& reader){
  return reader.print(os);
}

#endif //MINE_OCCT_DEMO_STEPREADER_HPP
