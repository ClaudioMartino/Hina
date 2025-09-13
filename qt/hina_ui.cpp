#include "hina_ui.h"
#include "ui_hina_ui.h"

#include <QFileDialog>

#include <unistd.h>
#include <filesystem>
#include "../src/hina.h"

hina_ui::hina_ui(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::hina_ui)
{
    ui->setupUi(this);

}

hina_ui::~hina_ui()
{
    delete ui;
}

QString path_dir;
QStringList files;

void hina_ui::on_buttonExplore_clicked()
{
    // Read directory content
    path_dir = QFileDialog::getExistingDirectory(this, tr("Open directory"));
    QDir dir(path_dir);

    dir.setSorting(QDir::Name);
    dir.setFilter(QDir::Files);

    files = dir.entryList();

    ui->listWidget->clear();
    ui->listWidget->addItems(files);

    // Enable spinbox
    ui->spinBoxCluster->setMaximum(files.count());
    ui->spinBoxCluster->setEnabled(true);
}


void hina_ui::on_buttonGo_clicked()
{
    std::string path_str = path_dir.toStdString();

    std::vector<std::string> images;
    for(auto& st : files)
        images.push_back(path_str + "/" + st.toStdString());

    // Read number of clusters
    size_t final_clusters = ui->spinBoxCluster->value();

    // Read clustering method
    int method = 0;
    if(ui->radioButton_0->isChecked())
        method = 0;
    else if(ui->radioButton_1->isChecked())
        method = 1;
    else if(ui->radioButton_2->isChecked())
        method = 2;
    else if(ui->radioButton_3->isChecked())
        method = 3;
    else if(ui->radioButton_4->isChecked())
        method = 4;
    else if(ui->radioButton_5->isChecked())
        method = 5;

    // Compute distance matrix
    DistanceMatrix d(files.count());
    d.compute(images, method, true);

    // Compute clusters
    Clusters c(final_clusters, images, path_str);
    c.compute(d, true);

    // Show result
    std::vector<std::vector<int>> c_idx = c.get();
    QStringList results;
    int cnt = 1;
    for (auto& idx_vec : c_idx) {
        std::string title = "CLUSTER " + std::to_string(cnt) + ":";
        results << QString::fromStdString(title);
        cnt++;
        for (int idx : idx_vec)
            results << QString::fromStdString(images[idx].erase(0, path_str.size()+1));
    }

    ui->listWidgetResult->clear();
    ui->listWidgetResult->addItems(results);
}

