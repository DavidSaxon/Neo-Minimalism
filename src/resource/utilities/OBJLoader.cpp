#include "src/resource/utilities/OBJLoader.hpp"

//FUNCTIONS
SharedShape obj_loader::loadOBJ(const std::string& path, GLuint tex) {

	//check if the file exists
	if (!util::file::fileExists(path)) {

		std::cout << path << " does not exist" << std::endl;
	}

	//all the vertex coords of the shape
	VertexCoords vCoords;
	//all the texture coords of the shape
	TexCoords tCoords;
	//the vertex coords in order
	VertexCoords vCoordsFinal;
	//the texture coords in order
	TexCoords tCoordsFinal;

	//open the file
	std::ifstream inFile(path.c_str());

	//iterate over the file
	while (inFile.good()) {

		//buffer for the line
		char lineBuffer[BUFFER_SIZE];

		//get the line
		inFile.getline(lineBuffer, BUFFER_SIZE);

		//conver to a string
		std::string line(lineBuffer);

		//get vertex coord
		if (util::str::beginsWith(line, "v ")) {

			//split
			util::str::ConstStringTuple split1 =
				util::str::splitAtStringDis(line, " ");
			util::str::ConstStringTuple split2 =
				util::str::splitAtStringDis(split1.second, " ");
			util::str::ConstStringTuple split3 =
				util::str::splitAtStringDis(split2.second, " ");

			vCoords.push_back(SharedVec3D(
				new util::vec::Vector3D(
				atof(split2.first.c_str()),
				atof(split3.first.c_str()),
				atof(split3.second.c_str()))));
		}
		//get texture coord
		else if (util::str::beginsWith(line, "vt ")) {

			//split
			util::str::ConstStringTuple split1 =
				util::str::splitAtStringDis(line, " ");
			util::str::ConstStringTuple split2 =
				util::str::splitAtStringDis(split1.second, " ");

			tCoords.push_back(SharedVec2D(
				new util::vec::Vector2D(
				atof(split2.first.c_str()),
				atof(split2.second.c_str()))));
		}
		//get face information
		else if (util::str::beginsWith(line, "f ")) {
 
			//split to discard f
			util::str::ConstStringTuple split1 =
				util::str::splitAtStringDis(line, " ");
			line = split1.second;

			//iterate over the 3 indices
			for (unsigned i = 0; i < 3; ++i) {

				//split at for first coords
				util::str::ConstStringTuple split2 =
					util::str::splitAtStringDis(line, " ");

				//split the vertex and texture indices
				util::str::ConstStringTuple split3 =
					util::str::splitAtStringDis(split2.first, "/");

				//add the new coords
				vCoordsFinal.push_back(
					vCoords[atoi(split3.first.c_str()) - 1]);
				tCoordsFinal.push_back(
					tCoords[atoi(split3.second.c_str()) - 1]);

				line = split2.second;
			}
		}
	}

	return SharedShape(new TriangleTex(tex, vCoordsFinal, tCoordsFinal));
}

SharedShape obj_loader::loadOBJ(const std::string& path,
	util::vec::Vector4D& col) {

	//all the vertex coords of the shape
	VertexCoords vCoords;
	//the vertex coords in order
	VertexCoords vCoordsFinal;

	//open the file
	std::ifstream inFile(path.c_str());

	//iterate over the file
	while (inFile.good()) {

		//buffer for the line
		char lineBuffer[BUFFER_SIZE];

		//get the line
		inFile.getline(lineBuffer, BUFFER_SIZE);

		//conver to a string
		std::string line(lineBuffer);

		//get vertex coord
		if (util::str::beginsWith(line, "v ")) {

			//split
			util::str::ConstStringTuple split1 =
				util::str::splitAtStringDis(line, " ");
			util::str::ConstStringTuple split2 =
				util::str::splitAtStringDis(split1.second, " ");
			util::str::ConstStringTuple split3 =
				util::str::splitAtStringDis(split2.second, " ");

			vCoords.push_back(SharedVec3D(
				new util::vec::Vector3D(
				atof(split2.first.c_str()),
				atof(split3.first.c_str()),
				atof(split3.second.c_str()))));
		}
		//get face information
		else if (util::str::beginsWith(line, "f ")) {

			//split
			util::str::ConstStringTuple split1 =
				util::str::splitAtStringDis(line, " ");
			util::str::ConstStringTuple split2 =
				util::str::splitAtStringDis(split1.second, " ");
			util::str::ConstStringTuple split3 =
				util::str::splitAtStringDis(split2.second, " ");

			vCoordsFinal.push_back(vCoords[atoi(split2.first.c_str()) - 1]);
			vCoordsFinal.push_back(vCoords[atoi(split3.first.c_str()) - 1]);
			vCoordsFinal.push_back(vCoords[atoi(split3.second.c_str()) - 1]);
		}
	}

	return SharedShape(new TriangleCol(col, vCoordsFinal));
}